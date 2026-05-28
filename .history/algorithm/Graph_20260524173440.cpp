#include "Graph.h"
#include <queue>
#include <iostream>

using namespace std;

// 这里只写 CampusGraph 类里的路径核心算法！

vector<int> CampusGraph::getShortestPath(int start, int end, int userType) {
    vector<int> path;
    
    // 你可以直接读取 this->adjList 进行 Dijkstra 操作了！
    // 比如：
    // for (const Edge& edge : adjList[currentNode]) { 
    //      if (userType == 1 && edge.roadType == 2) continue; 
    //      ... 
    // }
    
    return path;
}

vector<int> CampusGraph::getTSPRoute(int start, vector<int> targets, int userType) {
    // ... TSP 算法
}