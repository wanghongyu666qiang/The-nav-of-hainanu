#include "../Graph.h"

using namespace std;

bool addRoad(Graph& g, int from, int to, int weight, int type) {
    int fromIndex = getIdIndex(g.scenes, from);
    int toIndex = getIdIndex(g.scenes, to);
    if (fromIndex == -1 || toIndex == -1) return false;

    // ÐÞ¸ÄÁÚ½Ó¾ØÕó
    g.scenes[fromIndex].edges[toIndex] = {to, weight, type};
    g.scenes[toIndex].edges[fromIndex] = {from, weight, type};
    saveRoads(g, "data/road.txt");
    return true;
}
