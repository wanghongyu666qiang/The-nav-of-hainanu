#include "../Graph.h"

using namespace std;

bool updateRoad(Graph& g, int from, int to, int weight, int type) {
    int fromIndex = -1, toIndex = -1;
    for (int i = 0; i < g.scenes.size(); ++i) {
        if (g.scenes[i].id == from) fromIndex = i;
        if (g.scenes[i].id == to) toIndex = i;
    }
    if (fromIndex == -1 || toIndex == -1) return false;

    // 淇敼閭绘帴鐭╅樀
    if (g.scenes[fromIndex].edges[toIndex].weight != INT_MAX) {
        g.scenes[fromIndex].edges[toIndex].weight = weight;
        g.scenes[fromIndex].edges[toIndex].roadType = type;
        
        g.scenes[toIndex].edges[fromIndex].weight = weight;
        g.scenes[toIndex].edges[fromIndex].roadType = type;
        
        saveRoads(g, "data/road.txt");
        return true;
    }
    return false;
}
