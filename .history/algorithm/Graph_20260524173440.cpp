#include "Graph.h"
#include <queue>
#include <iostream>

using namespace std;

// 杩欓噷鍙啓 CampusGraph 绫婚噷鐨勮矾寰勬牳蹇冪畻娉曪紒

vector<int> CampusGraph::getShortestPath(int start, int end, int userType) {
    vector<int> path;
    
    // 浣犲彲浠ョ洿鎺ヨ鍙?this->adjList 杩涜 Dijkstra 鎿嶄綔浜嗭紒
    // 姣斿锛?
    // for (const Edge& edge : adjList[currentNode]) { 
    //      if (userType == 1 && edge.roadType == 2) continue; 
    //      ... 
    // }
    
    return path;
}

vector<int> CampusGraph::getTSPRoute(int start, vector<int> targets, int userType) {
    // ... TSP 绠楁硶
}