#include <iostream>
#include <vector>
#include "algorithm/Graph.h"

using namespace std;

int main() {
    CampusGraph graph;

    //  鍒濆鍖栨暟鎹?(鍔″繀纭txt璺緞姝ｇ‘)
    if (!graph.loadScenes("data/scene.txt") || !graph.loadRoads("data/road.txt")) {
        cout << "鏁版嵁鍔犺浇澶辫触锛? << endl;
        return 1;
    }
    cout << "鍦板浘鏁版嵁鍔犺浇鎴愬姛锛? << endl;

    // 娴嬭瘯
    int start = 1; // 1: 涓滃ぇ闂?
    int end = 5;   // 5: 鎬濇簮瀛﹀爞
    
    cout << "\n娴嬭瘯琛屼汉瀵昏矾 (鐢?1 鍘?5):" << endl;
    vector<int> path = graph.getShortestPath(start, end, 1);
    
    cout << "璺嚎: ";
    for (int id : path) {
        cout << graph.getSceneName(id) << " -> ";
    }
    cout << "缁撴潫" << endl;

    return 0;
}