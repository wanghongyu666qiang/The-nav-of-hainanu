#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
//这里，我们不使用#include <iostream>，保持头文件的纯净和高效。

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
    std::vector<Edge> edges; // ✨ 该景点出发的所有边，直接保存在它自己身上！
};

// 3. 把所有的图数据打包进一个大结构体里，方便传来传去，数据的大心脏
struct Graph {
    std::vector<Scene> scenes; // ✨ 不再使用map，所有景点按顺序存在动态数组里
};

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

// 算法函数 (algorithm.cpp 里)
// 传入 const Graph& g 代表算法只读取图，不修改图
std::vector<int> getShortestPath(const Graph& g, int start, int end, int userType);
std::vector<int> getTSPRoute(const Graph& g, int start, std::vector<int> targets, int userType);

#endif