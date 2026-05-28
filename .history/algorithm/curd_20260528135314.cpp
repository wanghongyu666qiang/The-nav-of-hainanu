#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// 1. 从文件读取景点数据
bool loadScenes(Graph& g, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    string line;
    // 先读一行废弃掉（因为第一行是中文表头："编号  名字  描述"）
    getline(file, line); 

    int id;
    string name, desc;
    // 使用 >> 能够自动跳过文件里的所有的空格和Tab
    while (file >> id >> name >> desc) {
        // 初始化时包含空 vector<Edge>()
        Scene s = {id, name, desc, vector<Edge>()};
        g.scenes.push_back(s);  // 直接放入数组
    }
    file.close();
    return true;
}

// 2. 从文件读取道路数据
bool loadRoads(Graph& g, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    string line;
    // 先读一行废弃掉表头（"起点  终点  距离  类型"）
    getline(file, line); 

    int from, to, weight, type;
    while (file >> from >> to >> weight >> type) {
        // 双向道路，两边都要加
        for (Scene& s : g.scenes) {
            if (s.id == from) s.edges.push_back({to, weight, type});
            if (s.id == to) s.edges.push_back({from, weight, type});
        }
    }
    file.close();
    return true;
}

// 3. 将内存里的景点数据写回文件（持久化）
bool saveScenes(const Graph& g, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) return false;

    file << "编号\t名字\t描述\n"; // 写入表头
    for (const Scene& s : g.scenes) {
        file << s.id << "\t" << s.name << "\t" << s.description << "\n";
    }
    file.close();
    return true;
}

// 4. 将内存里的道路数据写回文件（持久化）
bool saveRoads(const Graph& g, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) return false;

    file << "起点\t终点\t距离\t类型\n"; // 写入表头
    for (const Scene& s : g.scenes) {
        int from = s.id;
        for (const Edge& e : s.edges) {
            if (from < e.to) { // 解决无向图重复写入的问题
                file << from << "\t" << e.to << "\t" << e.weight << "\t" << e.roadType << "\n";
            }
        }
    }
    file.close();
    return true;
}

// ================== C U R D (增删改查) 业务代码 ==================

// 增加景点
bool addScene(Graph& g, int id, string name, string desc) {
    // 检查是否已经存在
    for (const Scene& s : g.scenes) {
        if (s.id == id) return false;
    }
    
    g.scenes.push_back({id, name, desc, vector<Edge>()});
    // 强制保存到文件
    saveScenes(g, "data/scene.txt");
    return true;
}

// 删除景点
bool deleteScene(Graph& g, int id) {
    bool found = false;

    auto it = g.scenes.begin();
    while (it != g.scenes.end()) {
        if (it->id == id) {
            // 找到景点本身，彻底删除
            it = g.scenes.erase(it);
            found = true;
        } else {
            // 删除其他景点通向该id的边
            auto& edges = it->edges;
            auto edgeIt = edges.begin();
            while (edgeIt != edges.end()) {
                if (edgeIt->to == id) {
                    edgeIt = edges.erase(edgeIt);
                } else {
                    ++edgeIt;
                }
            }
            ++it;
        }
    }

    if (!found) return false;

    // 更新文件
    saveScenes(g, "data/scene.txt");
    saveRoads(g, "data/road.txt");
    return true;
}

// 修改景点
bool updateScene(Graph& g, int id, string name, string desc) {
    for (Scene& s : g.scenes) {
        if (s.id == id) {
            s.name = name;
            s.description = desc;
            saveScenes(g, "data/scene.txt");
            return true;
        }
    }
    return false;
}

// 增加连接边（道路）
bool addRoad(Graph& g, int from, int to, int weight, int type) {
    bool fromFound = false, toFound = false;
    for (const Scene& s : g.scenes) {
        if (s.id == from) fromFound = true;
        if (s.id == to) toFound = true;
    }
    // 检查起点和终点是否存在
    if (!fromFound || !toFound) return false;

    for (Scene& s : g.scenes) {
        if (s.id == from) {
            bool dup = false;
            for (const auto& e : s.edges) if (e.to == to) dup = true;
            if (!dup) s.edges.push_back({to, weight, type});
        }
        if (s.id == to) {
            bool dup = false;
            for (const auto& e : s.edges) if (e.to == from) dup = true;
            if (!dup) s.edges.push_back({from, weight, type});
        }
    }
    
    saveRoads(g, "data/road.txt");
    return true;
}

// 删除连接边（道路）
bool deleteRoad(Graph& g, int from, int to) {
    bool found = false;
    
    for (Scene& s : g.scenes) {
        if (s.id == from) {
            auto it = s.edges.begin();
            while (it != s.edges.end()) {
                if (it->to == to) {
                    it = s.edges.erase(it);
                    found = true;
                } else {
                    ++it;
                }
            }
        }
        if (s.id == to) {
            auto it = s.edges.begin();
            while (it != s.edges.end()) {
                if (it->to == from) {
                    it = s.edges.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }

    if (found) saveRoads(g, "data/road.txt");
    return found;
}

// 修改边（重新设置权重/类型）
bool updateRoad(Graph& g, int from, int to, int weight, int type) {
    bool found = false;
    
    for (Scene& s : g.scenes) {
        if (s.id == from) {
            for (Edge& e : s.edges) {
                if (e.to == to) {
                    e.weight = weight;
                    e.roadType = type;
                    found = true;
                }
            }
        }
    if (found) saveRoads(g, "data/road.txt");
    return found;
}

// 提取出行走专用的邻接矩阵图，供算法使用
Graph getWalkGraph(const Graph& g) {
    Graph res = g;
    // 构建邻接矩阵形式的 edges 配合 Dijkstra 的索引访问
    for (int i = 0; i < res.scenes.size(); ++i) {
        vector<Edge> matrixEdges(res.scenes.size());
        for (int j = 0; j < res.scenes.size(); ++j) {
            matrixEdges[j] = {res.scenes[j].id, INT_MAX, 0}; 
        }
        matrixEdges[i].weight = 0; // 自身到自身距离为 0
        
        for (const Edge& e : g.scenes[i].edges) {
            if (e.roadType == 0) { // 仅提取人行道
                int targetIndex = -1;
                for (int k = 0; k < res.scenes.size(); ++k) {
                    if (res.scenes[k].id == e.to) {
                        targetIndex = k;
                        break;
                    }
                }
                if (targetIndex != -1) {
                    matrixEdges[targetIndex].weight = e.weight;
                }
            }
        }
        res.scenes[i].edges = matrixEdges;
    }
    return res;
}

// 提取出车行专用的邻接矩阵图，供算法使用
Graph getDriveGraph(const Graph& g) {
    Graph res = g;
    for (int i = 0; i < res.scenes.size(); ++i) {
        vector<Edge> matrixEdges(res.scenes.size());
        for (int j = 0; j < res.scenes.size(); ++j) {
            matrixEdges[j] = {res.scenes[j].id, INT_MAX, 1}; 
        }
        matrixEdges[i].weight = 0; 
        
        for (const Edge& e : g.scenes[i].edges) {
            if (e.roadType == 1) { // 仅提取车道
                int targetIndex = -1;
                for (int k = 0; k < res.scenes.size(); ++k) {
                    if (res.scenes[k].id == e.to) {
                        targetIndex = k;
                        break;
                    }
                }
                if (targetIndex != -1) {
                    matrixEdges[targetIndex].weight = e.weight;
                }
            }
        }
        res.scenes[i].edges = matrixEdges;
    }
    return res;
}