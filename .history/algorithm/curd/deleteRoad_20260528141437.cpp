#include "../Graph.h"
#include <algorithm>

using namespace std;

bool deleteRoad(Graph& g, int from, int to) {
    bool found = false;
    for (Scene& s : g.scenes) {
        if (s.id == from || s.id == to) { // 同时处理正反双向边
            int targetId = (s.id == from) ? to : from;
            auto it = remove_if(s.edges.begin(), s.edges.end(), 
                [targetId](const Edge& e) { return e.to == targetId; });
            if (it != s.edges.end()) {
                s.edges.erase(it, s.edges.end());
                found = true;
            }
        }
    }
    if (found) saveRoads(g, "data/road.txt");
    return found;
}
