#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <map>

// 1. 景点结构体 (根据你最新的txt，去掉了X和Y)
struct Scene {
    int id;
    std::string name;
    std::string description;
};

// 2. 边结构体
struct Edge {
    int to;
    int weight;
    int roadType; 
};

// 3. 把所有的图数据打包进一个大结构体里，方便传来传去
struct Graph {
    std::map<int, Scene> scenes;
    std::map<int, std::vector<Edge>> adjList;
};

// ==========================================
// ====== 所有的全局函数声明 (向外导出) ======
// ==========================================

// 后勤函数 (以前在 curd.cpp 里)
// 传入 Graph& g 代表我们要修改这幅图
bool loadScenes(Graph& g, const std::string& filename);
bool loadRoads(Graph& g, const std::string& filename);
bool saveScenes(const Graph& g, const std::string& filename);

bool addScene(Graph& g, int id, std::string name, std::string desc);
bool deleteScene(Graph& g, int id);
bool addRoad(Graph& g, int from, int to, int weight, int type);

// 算法函数 (以前在 algorithm.cpp 里)
// 传入 const Graph& g 代表算法只读取图，不修改图
std::vector<int> getShortestPath(const Graph& g, int start, int end, int userType);

#endif