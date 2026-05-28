#include "../Graph.h"

using namespace std;

bool deleteRoad(Graph& g, int from, int to) {
    int fromIndex = -1, toIndex = -1;
    for (int i = 0; i < g.scenes.size(); ++i) {
        if (g.scenes[i].id == from) fromIndex = i;
        if (g.scenes[i].id == to) toIndex = i;
    }
    if (fromIndex == -1 || toIndex == -1) return false;

    // 修改为邻接矩阵的删除（即距离变为 INT_MAX）
    if (g.scenes[fromIndex].edges[toIndex].weight != INT_MAX) {
        g.scenes[fromIndex].edges[toIndex] = {to, INT_MAX, -1};
        g.scenes[toIndex].edges[fromIndex] = {from, INT_MAX, -1};
        saveRoads(g, "data/road.txt");
        return true;
    }
    return false;
}
