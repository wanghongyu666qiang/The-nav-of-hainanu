#include "Graph.h"
#include <queue>
#include <iostream>

using namespace std;

vector<int> getShortestPath(const Graph& g, int startId, int endId, int userType) {
    // 1. 找到起点和终点在数组中的索引
    int startIndex = -1, endIndex = -1;
    for (int i = 0; i < g.scenes.size(); i++) {
        if (g.scenes[i].id == startId) startIndex = i;
        if (g.scenes[i].id == endId) endIndex = i;
    }
    if (startIndex == -1 || endIndex == -1) return {};

    // 采用真正适配“邻接表”的 Dijkstra 算法
    int n = g.scenes.size();
    vector<int> result;
    vector<int> path(n, -1);      // 存储路径(存的是index)
    vector<int> dist(n, INT_MAX); // 存储距离
    vector<int> visited(n, 0);    // 存储访问状态, 0未访问, 1已访问

    // 初始化起点
    dist[startIndex] = 0;

    for (int i = 0; i < n; i++) {
        // 找到没被访问且距离最短的节点
        int mini = INT_MAX;
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (visited[j] == 0 && dist[j] < mini) {
                mini = dist[j];
                u = j;
            }
        }
        if (u == -1) break; // 剩余节点不可达
        visited[u] = 1;

        // 根据邻接表更新 u 的邻居节点的距离
        for (const Edge& edge : g.scenes[u].edges) {
            // 根据 userType 过滤道路，0为人行道，1为车道。如果 userType 为0，只走0；如果是1，代表车，通常所有的都能走或只走车道？假设等于 userType 才能走
            if (edge.roadType != userType) continue; 

            // 在邻接表中，edge.to 存的是景点的 ID（1,2,3...），我们需要找到它在数组中的索引
            int v = -1;
            for (int k = 0; k < n; k++) {
                if (g.scenes[k].id == edge.to) {
                    v = k;
                    break;
                }
            }
            if (v == -1) continue;

            // 松弛操作更新距离
            if (dist[u] + edge.weight < dist[v]) {
                dist[v] = dist[u] + edge.weight;
                path[v] = u; // 记录前驱节点
            }
        }
    }

    // 从终点开始回溯路径，把索引转回 ID
    int current = endIndex;
    if (dist[current] == INT_MAX) return result; // 不可达

    while (current != -1) {
        result.push_back(g.scenes[current].id);
        current = path[current];
    }
    std::reverse(result.begin(), result.end());
    return result;
}

vector<int> getTSPRoute(const Graph& g, int start, vector<int> targets, int userType) {
    vector<int> route;
    // ... TSP 算法
    return route;
}