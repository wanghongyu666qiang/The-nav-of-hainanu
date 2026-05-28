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
        Scene s = {id, name, desc};
        g.scenes[id] = s;  // 把读到的数据放进传进来的 g 里面
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
        g.adjList[from].push_back({to, weight, type});
        g.adjList[to].push_back({from, weight, type});
    }
    file.close();
    return true;
}

// 3. 将内存里的景点数据写回文件（持久化）
bool saveScenes(const Graph& g, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) return false;

    file << "编号\t名字\t描述\n"; // 写入表头
    for (const auto& pair : g.scenes) {
        const Scene& s = pair.second;
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
    // 为了防止双向边写入两次，可以用二维map或只在 from < to 时写入
    for (const auto& pair : g.adjList) {
        int from = pair.first;
        for (const Edge& e : pair.second) {
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
    if (g.scenes.find(id) != g.scenes.end()) return false; 
    
    g.scenes[id] = {id, name, desc};
    // 强制保存到文件
    saveScenes(g, "data/scene.txt");
    return true;
}

// 删除景点
bool deleteScene(Graph& g, int id) {
    if (g.scenes.find(id) == g.scenes.end()) return false;

    // 1. 删除景点信息
    g.scenes.erase(id);

    // 2. 删除与该景点直接相关的邻接链表
    g.adjList.erase(id);

    // 3. 遍历其他所有景点的链表，删除通向这个 id 的边
    for (auto& pair : g.adjList) {
        vector<Edge>& edges = pair.second;
        for (auto it = edges.begin(); it != edges.end(); ) {
            if (it->to == id) {
                it = edges.erase(it);
            } else {
                ++it;
            }
        }
    }

    // 更新文件
    saveScenes(g, "data/scene.txt");
    saveRoads(g, "data/road.txt");
    return true;
}

// 修改景点
bool updateScene(Graph& g, int id, string name, string desc) {
    if (g.scenes.find(id) == g.scenes.end()) return false;
    
    g.scenes[id].name = name;
    g.scenes[id].description = desc;
    
    saveScenes(g, "data/scene.txt");
    return true;
}

// 增加连接边（道路）
bool addRoad(Graph& g, int from, int to, int weight, int type) {
    // 检查起点和终点是否存在
    if (g.scenes.find(from) == g.scenes.end() || g.scenes.find(to) == g.scenes.end()) {
        return false;
    }

    // 检查是否已经有这条边（防止重复添加）
    for (const Edge& e : g.adjList[from]) {
        if (e.to == to) return false;
    }

    g.adjList[from].push_back({to, weight, type});
    g.adjList[to].push_back({from, weight, type}); // 无向图
    
    saveRoads(g, "data/road.txt");
    return true;
}

// 删除连接边（道路）
bool deleteRoad(Graph& g, int from, int to) {
    bool found = false;
    
    // 从 from 的链表中删除 to
    auto& fromEdges = g.adjList[from];
    for (auto it = fromEdges.begin(); it != fromEdges.end(); ) {
        if (it->to == to) {
            it = fromEdges.erase(it);
            found = true;
        } else {
            ++it;
        }
    }
    
    // 从 to 的链表中删除 from
    auto& toEdges = g.adjList[to];
    for (auto it = toEdges.begin(); it != toEdges.end(); ) {
        if (it->to == from) {
            it = toEdges.erase(it);
        } else {
            ++it;
        }
    }

    if (found) saveRoads(g, "data/road.txt");
    return found;
}

// 修改边（重新设置权重/类型）
bool updateRoad(Graph& g, int from, int to, int weight, int type) {
    bool found = false;
    
    for (Edge& e : g.adjList[from]) {
        if (e.to == to) {
            e.weight = weight;
            e.roadType = type;
            found = true;
            break;
        }
    }
    for (Edge& e : g.adjList[to]) {
        if (e.to == from) {
            e.weight = weight;
            e.roadType = type;
            found = true;
            break;
        }
    }

    if (found) saveRoads(g, "data/road.txt");
    return found;
}