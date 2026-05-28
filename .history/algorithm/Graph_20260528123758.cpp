#include "Graph.h"
#include <queue>
#include <iostream>

using namespace std;



vector<int> getShortestPath(const Graph& g, int start, int end, int userType) {//采用dijistra算法
    vector<int> path;//这里用动态数组来存储路径，最后返回给调用者
    
    // 比如可以通过遍历 scenes 找到当前节点的 edges 进行 Dijkstra 操作了！
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
    // ... TSP 算法
    return route;
}