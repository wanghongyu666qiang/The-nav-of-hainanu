#include "../Graph.h"
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
    while (file >> id >> name >> desc) {
        // 先建立空的 edges
        Scene s = {id, name, desc, vector<Edge>()};
        g.scenes.push_back(s);
    }
    file.close();

    // 在读取完所有景点后，初始化每个景点的邻接矩阵数据结构
    int n = g.scenes.size();
    for (int i = 0; i < n; ++i) {
        g.scenes[i].edges.resize(n); // 大小与景点数量相同
        for (int j = 0; j < n; ++j) {
            // 用每个位置对应的景点 ID 填充 to 字段，权重初始化为 INT_MAX
            g.scenes[i].edges[j] = {g.scenes[j].id, INT_MAX, -1};
        }
        // 自己到自己的距离为 0
        g.scenes[i].edges[i].weight = 0;
    }
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
        // 因为是邻接矩阵，我们需要通过 ID 找到对应的索引
        int fromIndex = -1, toIndex = -1;
        for (int i = 0; i < g.scenes.size(); ++i) {
            if (g.scenes[i].id == from) fromIndex = i;
            if (g.scenes[i].id == to) toIndex = i;
        }

        // 双向赋值（覆盖原本的 INT_MAX）
        if (fromIndex != -1 && toIndex != -1) {
            g.scenes[fromIndex].edges[toIndex].weight = weight;
            g.scenes[fromIndex].edges[toIndex].roadType = type;
            
            g.scenes[toIndex].edges[fromIndex].weight = weight;
            g.scenes[toIndex].edges[fromIndex].roadType = type;
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
    for (int i = 0; i < g.scenes.size(); ++i) {
        for (int j = i + 1; j < g.scenes.size(); ++j) {
            // 只要不是无穷大，且不是自身，说明有一条路
            if (g.scenes[i].edges[j].weight != INT_MAX) {
                file << g.scenes[i].id << "\t" 
                     << g.scenes[j].id << "\t" 
                     << g.scenes[i].edges[j].weight << "\t" 
                     << g.scenes[i].edges[j].roadType << "\n";
            }
        }
    }
    file.close();
    return true;
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
        
        for (const Edge& e : g.scenes[i].edges) {//来个类python的for循环，遍历每条边
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
