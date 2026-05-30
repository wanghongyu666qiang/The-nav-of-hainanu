#include "Graph.h"
#include <queue>
#include <iostream>
using namespace std;

void getshortestpath(const Graph& g,int start,int end,int userType) {//閲囩敤dijistra绠楁硶
    vector<int> result;
    int n = (int)g.scenes.size();
    if (n == 0) {
        cout << "鍥句负绌猴紝鏃犳硶鏌ヨ鏈€鐭矾寰勩€? << endl;
        return;
    }

    vector<int> path(n, -1); // 瀛樺偍璺緞鍓嶉┍
    vector<int> dist(n, INT_MAX); // 瀛樺偍璺濈锛屽垵濮嬪寲涓烘棤绌峰ぇ
    vector<char> visited(n, 0); // 瀛樺偍璁块棶鐘舵€?0琛ㄧず鏈闂紝1琛ㄧず宸茶闂?

    // 鍒濆鍖栵細浠庤捣鐐瑰嚭鍙戝埌鎵€鏈夎妭鐐圭殑鐩存帴璺濈
    for (int i = 0; i < n; ++i) {
        dist[i] = g.scenes[start].edges[i].weight;
        if (dist[i] != INT_MAX) path[i] = start;
    }
    dist[start] = 0;
    path[start] = -1;

    // Dijkstra 涓诲惊鐜?
    for (int iter = 0; iter < n; ++iter) {
        int mini = INT_MAX;
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && dist[j] < mini) {
                mini = dist[j];
                u = j;
            }
        }
        if (u == -1) break; // 鍓╀笅鑺傜偣涓嶅彲杈?
        visited[u] = 1;

        // 鏉惧紱 u 鐨勬墍鏈夐偦灞?
        for (int v = 0; v < (int)g.scenes[u].edges.size(); ++v) {
            if (visited[v]) continue;
            int w = g.scenes[u].edges[v].weight;
            if (dist[u] != INT_MAX && w != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                path[v] = u;
            }
        }
    }

    if (dist[end] == INT_MAX) {
        cout << "鏃犲彲杈捐矾寰勶紙鎴栭€氳鏂瑰紡闄愬埗瀵艰嚧涓嶅彲杈撅級銆? << endl;
        return;
    }

    // 浠?end 鍥炴函璺緞
    int current = end;
    while (current != -1) {
        result.push_back(current);
        current = path[current];
    }
    std::reverse(result.begin(), result.end());

    cout << "鏈€鐭矾寰勯暱搴︿负锛? << dist[end] << endl;
    cout << "璺緞涓猴細";
    for (int i = 0; i < (int)result.size(); ++i) {
        // 杈撳嚭鏇村弸濂界殑鏍煎紡锛氱储寮?鍚嶅瓧
        cout << result[i] << ":" << g.scenes[result[i]].name;
        if (i + 1 < (int)result.size()) cout << " -> ";
    }
    cout << endl;

}

vector<int> getTSPRoute(const Graph& g, int start, vector<int> targets, int userType) {
    vector<int> route;
    // ... TSP 绠楁硶
    return route;
}