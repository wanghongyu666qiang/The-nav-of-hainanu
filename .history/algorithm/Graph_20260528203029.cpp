#include "Graph.h"
#include <queue>
#include <iostream>

using namespace std;

vector<int> getShortestPath(const Graph& g, int startId, int endId, int userType) {
    // 1. 鎵惧埌璧风偣鍜岀粓鐐瑰湪鏁扮粍涓殑绱㈠紩
    int startIndex = -1, endIndex = -1;
    for (int i = 0; i < g.scenes.size(); i++) {
        if (g.scenes[i].id == startId) startIndex = i;
        if (g.scenes[i].id == endId) endIndex = i;
    }
    if (startIndex == -1 || endIndex == -1) return {};

    // 閲囩敤鐪熸閫傞厤鈥滈偦鎺ヨ〃鈥濈殑 Dijkstra 绠楁硶
    int n = g.scenes.size();
    vector<int> result;
    vector<int> path(n, -1);      // 瀛樺偍璺緞(瀛樼殑鏄痠ndex)
    vector<int> dist(n, INT_MAX); // 瀛樺偍璺濈
    vector<int> visited(n, 0);    // 瀛樺偍璁块棶鐘舵€? 0鏈闂? 1宸茶闂?

    // 鍒濆鍖栬捣鐐?
    dist[startIndex] = 0;

    for (int i = 0; i < n; i++) {
        // 鎵惧埌娌¤璁块棶涓旇窛绂绘渶鐭殑鑺傜偣
        int mini = INT_MAX;
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (visited[j] == 0 && dist[j] < mini) {
                mini = dist[j];
                u = j;
            }
        }
        if (u == -1) break; // 鍓╀綑鑺傜偣涓嶅彲杈?
        visited[u] = 1;

        // 鏍规嵁閭绘帴琛ㄦ洿鏂?u 鐨勯偦灞呰妭鐐圭殑璺濈
        for (const Edge& edge : g.scenes[u].edges) {
            // 鏍规嵁 userType 杩囨护閬撹矾锛?涓轰汉琛岄亾锛?涓鸿溅閬撱€傚鏋?userType 涓?锛屽彧璧?锛涘鏋滄槸1锛屼唬琛ㄨ溅锛岄€氬父鎵€鏈夌殑閮借兘璧版垨鍙蛋杞﹂亾锛熷亣璁剧瓑浜?userType 鎵嶈兘璧?
            if (edge.roadType != userType) continue; 

            // 鍦ㄩ偦鎺ヨ〃涓紝edge.to 瀛樼殑鏄櫙鐐圭殑 ID锛?,2,3...锛夛紝鎴戜滑闇€瑕佹壘鍒板畠鍦ㄦ暟缁勪腑鐨勭储寮?
            int v = -1;
            for (int k = 0; k < n; k++) {
                if (g.scenes[k].id == edge.to) {
                    v = k;
                    break;
                }
            }
            if (v == -1) continue;

            // 鏉惧紱鎿嶄綔鏇存柊璺濈
            if (dist[u] + edge.weight < dist[v]) {
                dist[v] = dist[u] + edge.weight;
                path[v] = u; // 璁板綍鍓嶉┍鑺傜偣
            }
        }
    }

    // 浠庣粓鐐瑰紑濮嬪洖婧矾寰勶紝鎶婄储寮曡浆鍥?ID
    int current = endIndex;
    if (dist[current] == INT_MAX) return result; // 涓嶅彲杈?

    while (current != -1) {
        result.push_back(g.scenes[current].id);
        current = path[current];
    }
    std::reverse(result.begin(), result.end());
    return result;
}

vector<int> getTSPRoute(const Graph& g, int start, vector<int> targets, int userType) {
    vector<int> route;
    // ... TSP 绠楁硶
    return route;
}