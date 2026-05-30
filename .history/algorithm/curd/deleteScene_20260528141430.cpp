#include "../Graph.h"
#include <algorithm>

using namespace std;

bool deleteScene(Graph& g, int id) {
    // 1. 绠€鍖栫殑鍒犻櫎瀵瑰簲鏅偣鏈韩
    auto it = remove_if(g.scenes.begin(), g.scenes.end(), [id](const Scene& s) { return s.id == id; });
    if (it == g.scenes.end()) return false; // 娌℃壘鍒?
    g.scenes.erase(it, g.scenes.end());

    // 2. 绠€鍖栫殑鍒犻櫎鍏朵粬鏅偣杩炴帴鍒拌id鐨勮竟
    for (Scene& s : g.scenes) {
        s.edges.erase(remove_if(s.edges.begin(), s.edges.end(), 
            [id](const Edge& e) { return e.to == id; }), s.edges.end());
    }

    saveScenes(g, "data/scene.txt");
    saveRoads(g, "data/road.txt");
    return true;
}
