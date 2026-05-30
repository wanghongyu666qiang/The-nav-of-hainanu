锘?#include "../Graph.h"

using namespace std;

//娣囶喗鏁奸崘鍛摠娑擃厾娈戦崶鐐殶閹诡喚绮ㄩ弸鍕剁礉楠炶泛鐨㈡穱顔芥暭閹镐椒绠欓崠鏍у煂閺傚洣娆?
bool addRoad(Graph& g, int from, int to, int weight, int type) {
    int fromIndex = -1, toIndex = -1;
    for (int i = 0; i < g.scenes.size(); ++i) {
        if (g.scenes[i].id == from) fromIndex = i;
        if (g.scenes[i].id == to) toIndex = i;
    }
    if (fromIndex == -1 || toIndex == -1) return false;

    // 娣囶喗鏁奸柇缁樺复閻晠妯€
    g.scenes[fromIndex].edges[toIndex] = {to, weight, type};
    g.scenes[toIndex].edges[fromIndex] = {from, weight, type};
    
    // 鐏忓棔鎱ㄩ弨瑙勫瘮娑斿懎瀵查崚鐗堟瀮娴??
    return saveRoads(g, "data/road.txt");
}
