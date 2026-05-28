#include "../Graph.h"

using namespace std;

bool addRoad(Graph& g, int from, int to, int weight, int type) {
    int fromIndex = -1, toIndex = -1;
    for (int i = 0; i < g.scenes.size(); ++i) {
        if (g.scenes[i].id == from) fromIndex = i;
        if (g.scenes[i].id == to) toIndex = i;
    }
    if (fromIndex == -1 || toIndex == -1) return false;

    // 修改邻接矩阵
    g.scenes[fromIndex].edges[toIndex] = {to, weight, type};
    g.scenes[toIndex].edges[fromIndex] = {from, weight, type};
    
    return true;
}
