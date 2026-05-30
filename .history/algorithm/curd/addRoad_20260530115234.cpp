#include "../Graph.h"

using namespace std;

//淇敼鍐呭瓨涓殑鍥炬暟鎹粨鏋勶紝骞跺皢淇敼鎸佷箙鍖栧埌鏂囦欢
bool addRoad(Graph& g, int from, int to, int weight, int type) {
    int fromIndex = -1, toIndex = -1;
    for (int i = 0; i < g.scenes.size(); ++i) {
        if (g.scenes[i].id == from) fromIndex = i;
        if (g.scenes[i].id == to) toIndex = i;
    }
    if (fromIndex == -1 || toIndex == -1) return false;

    // 淇敼閭绘帴鐭╅樀
    g.scenes[fromIndex].edges[toIndex] = {to, weight, type};
    g.scenes[toIndex].edges[fromIndex] = {from, weight, type};
    
    // 灏嗕慨鏀规寔涔呭寲鍒版枃浠?
    return saveRoads(g, "data/road.txt");
}
