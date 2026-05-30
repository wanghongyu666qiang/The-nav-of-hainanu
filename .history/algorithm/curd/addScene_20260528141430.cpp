#include "../Graph.h"
#include <algorithm>

using namespace std;

bool addScene(Graph& g, int id, string name, string desc) {
    for (const Scene& s : g.scenes) if (s.id == id) return false;
    g.scenes.push_back({id, name, desc, vector<Edge>()});
    return saveScenes(g, "data/scene.txt");
}
