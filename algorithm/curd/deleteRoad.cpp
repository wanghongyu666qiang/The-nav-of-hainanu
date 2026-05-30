#include "../Graph.h"

using namespace std;

bool deleteRoad(Graph& g, int from, int to) {
    int fromIndex = getIdIndex(g.scenes, from);
    int toIndex = getIdIndex(g.scenes, to);
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
