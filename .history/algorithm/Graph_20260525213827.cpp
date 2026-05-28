#include "Graph.h"
#include <queue>
#include <iostream>

using namespace std;

// 这里写路径核心算法！

vector<int> getShortestPath(const Graph& g, int start, int end, int userType) {
    vector<int> path;
    
    // 你可以直接读取 g.adjList 进行 Dijkstra 操作了！
    // 比如：
    // for (const Edge& edge : g.adjList.at(currentNode)) { 
    //      if (userType == 1 && edge.roadType == 2) continue; 
    //      ... 
    // }
    
    return path;
}

vector<int> getTSPRoute(const Graph& g, int start, vector<int> targets, int userType) {
    vector<int> route;
    // ... TSP 算法
    return route;
}