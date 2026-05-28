#include "../Graph.h"
#include <algorithm>

using namespace std;

bool addRoad(Graph& g, int from, int to, int weight, int type) {
    bool fromFound = false, toFound = false;
    for (const Scene& s : g.scenes) {
        if (s.id == from) fromFound = true;
        if (s.id == to) toFound = true;
    }
    if (!fromFound || !toFound) return false;

    // 添加双向边（加上避免重复的判断）
    for (Scene& s : g.scenes) {
        if (s.id == from) {
            auto it = find_if(s.edges.begin(), s.edges.end(), [to](const Edge& e){ return e.to == to; });
            if (it == s.edges.end()) s.edges.push_back({to, weight, type});
        }
        if (s.id == to) {
            auto it = find_if(s.edges.begin(), s.edges.end(), [from](const Edge& e){ return e.to == from; });
            if (it == s.edges.end()) s.edges.push_back({from, weight, type});
        }
    }
    return saveRoads(g, "data/road.txt");
}
