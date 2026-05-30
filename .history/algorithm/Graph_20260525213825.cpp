#include "Graph.h"
#include <queue>
#include <iostream>

using namespace std;

// 杩欓噷鍐欒矾寰勬牳蹇冪畻娉曪紒

vector<int> getShortestPath(const Graph& g, int start, int end, int userType) {
    vector<int> path;
    
    // 浣犲彲浠ョ洿鎺ヨ鍙?g.adjList 杩涜 Dijkstra 鎿嶄綔浜嗭紒
    // 姣斿锛?
    // for (const Edge& edge : g.adjList.at(currentNode)) { 
    //      if (userType == 1 && edge.roadType == 2) continue; 
    //      ... 
    // }
    
    return path;
}

vector<int> getTSPRoute(const Graph& g, int start, vector<int> targets, int userType) {
    vector<int> route;
    // ... TSP 绠楁硶
    return route;
}