#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include<climits>//INT_MAX
//这里，我们不使用using namespace std;，而是直接在需要的地方加上std::，这样可以避免命名冲突。

// 1. 边结构体，其实就是一个节点的邻居，包含权重和道路类型
struct Edge {
    int to;
    int weight;
    int roadType; 
};

// 2. 景点结构体 
struct Scene {
    int id;
    std::string name;
    std::string description;
    std::vector<Edge> edges;
};

// 3. 把所有的图数据打包进一个大结构体里，方便传来传去，数据的大心脏
struct Graph {
    std::vector<Scene> scenes;//这个包含了每个景点的信息和他的每条边的信息（邻接表）
};


inline int getIdIndex(const std::vector<Scene>& scenes, int id) {
    for (int i = 0; i < (int)scenes.size(); ++i)
        if (scenes[i].id == id) return i;
    return -1;
}

// 后勤函数（包括增删改查） (在 curd.cpp 里)
// 传入 Graph& g 代表我们要修改这幅图
bool loadScenes(Graph& g, const std::string& filename);
bool loadRoads(Graph& g, const std::string& filename);
bool saveScenes(const Graph& g, const std::string& filename);
bool saveRoads(const Graph& g, const std::string& filename);
bool addScene(Graph& g, int id, std::string name, std::string desc);
bool deleteScene(Graph& g, int id);
bool updateScene(Graph& g, int id, std::string name, std::string desc);
bool addRoad(Graph& g, int from, int to, int weight, int type);
bool deleteRoad(Graph& g, int from, int to);
bool updateRoad(Graph& g, int from, int to, int weight, int type);
void printScenes(const Graph& g);

// 工具函数：根据混合表图，生成纯供Dijkstra读取的邻接矩阵图（解耦人行道与车道）
Graph getFilteredGraph(const Graph& g, int roadType);

// 算法函数 (algorithm.cpp 里)
// 传入 const Graph& g 代表算法只读取图，不修改图
void getshortestpath(const Graph& g, int start, int end, int userType);
void findAllPaths(const Graph& g, int start, int end);


#endif