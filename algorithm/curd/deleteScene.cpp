#include "../Graph.h"
#include <algorithm>

using namespace std;

bool deleteScene(Graph& g, int id) {
    int index = -1;
    for (int i = 0; i < g.scenes.size(); ++i) {
        if (g.scenes[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) return false;

    // 1. 删除该景点结点
    g.scenes.erase(g.scenes.begin() + index);

    // 2. 对于剩余的景点，删除对应维度邻接矩阵的列（缩减那个元素）
    for (Scene& s : g.scenes) {
        s.edges.erase(s.edges.begin() + index);
    }

    saveScenes(g, "data/scene.txt");
    saveRoads(g, "data/road.txt");
    return true;
}
