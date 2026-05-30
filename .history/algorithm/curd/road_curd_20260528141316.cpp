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

    // 娣诲姞鍙屽悜杈癸紙鍔犱笂閬垮厤閲嶅鐨勫垽鏂級
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

bool deleteRoad(Graph& g, int from, int to) {
    bool found = false;
    for (Scene& s : g.scenes) {
        if (s.id == from || s.id == to) { // 鍚屾椂澶勭悊姝ｅ弽鍙屽悜杈?
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
