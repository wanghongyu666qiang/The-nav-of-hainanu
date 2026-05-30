#include "Graph.h"
#include <queue>
#include <iostream>

using namespace std;



vector<int> getShortestPath(const Graph& g, int start, int end, int userType) {//閲囩敤dijistra绠楁硶
    vector<int> path;//杩欓噷鐢ㄥ姩鎬佹暟缁勬潵瀛樺偍璺緞锛屾渶鍚庤繑鍥炵粰璋冪敤鑰?
    
    // 姣斿鍙互閫氳繃閬嶅巻 scenes 鎵惧埌褰撳墠鑺傜偣鐨?edges 杩涜 Dijkstra 鎿嶄綔浜嗭紒
    // for (const Scene& s : g.scenes) {
    //      if (s.id == currentNode) {
    //          for (const Edge& edge : s.edges) {
    //              if (userType == 1 && edge.roadType == 2) continue; 
    //              ... 
    //          }
    //      }
    // }
    int path[]





    return path;
}

vector<int> getTSPRoute(const Graph& g, int start, vector<int> targets, int userType) {
    vector<int> route;
    // ... TSP 绠楁硶
    return route;
}