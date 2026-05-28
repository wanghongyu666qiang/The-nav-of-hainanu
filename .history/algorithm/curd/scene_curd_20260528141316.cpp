#include "../Graph.h"
#include <algorithm>

using namespace std;

bool addScene(Graph& g, int id, string name, string desc) {
    for (const Scene& s : g.scenes) if (s.id == id) return false;
    g.scenes.push_back({id, name, desc, vector<Edge>()});
    return saveScenes(g, "data/scene.txt");
}

bool updateScene(Graph& g, int id, string name, string desc) {
    for (Scene& s : g.scenes) {
        if (s.id == id) {
            s.name = name;
            s.description = desc;
            return saveScenes(g, "data/scene.txt");
        }
    }
    return false;
}

bool deleteScene(Graph& g, int id) {
    // 1. 简化的删除对应景点本身
    auto it = remove_if(g.scenes.begin(), g.scenes.end(), [id](const Scene& s) { return s.id == id; });
    if (it == g.scenes.end()) return false; // 没找到
    g.scenes.erase(it, g.scenes.end());

    // 2. 简化的删除其他景点连接到该id的边
    for (Scene& s : g.scenes) {
        s.edges.erase(remove_if(s.edges.begin(), s.edges.end(), 
            [id](const Edge& e) { return e.to == id; }), s.edges.end());
    }

    saveScenes(g, "data/scene.txt");
    saveRoads(g, "data/road.txt");
    return true;
}
