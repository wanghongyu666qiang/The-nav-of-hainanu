#include "../Graph.h"

using namespace std;

bool updateRoad(Graph& g, int from, int to, int weight, int type) {
    bool found = false;
    for (Scene& s : g.scenes) {
        if (s.id == from) {
            for (Edge& e : s.edges) {
                if (e.to == to) { e.weight = weight; e.roadType = type; found = true; }
            }
        }
        // 鐢变簬鏄弻鍚戝浘锛屼篃瑕佷慨鏀瑰弽鍚戣竟
        if (s.id == to) {
            for (Edge& e : s.edges) {
                if (e.to == from) { e.weight = weight; e.roadType = type; found = true; }
            }
        }
    }
    if (found) saveRoads(g, "data/road.txt");
    return found;
}
