#include "../Graph.h"

using namespace std;

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
