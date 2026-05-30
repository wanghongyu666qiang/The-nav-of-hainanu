#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// 娉ㄦ剰鍙傛暟閲屾湁 Graph& g
bool loadScenes(Graph& g, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    string line;
    // 鍏堣涓€琛屽簾寮冩帀锛堝洜涓轰綘绗竴琛屾槸涓枃琛ㄥご锛?缂栧彿  鍚嶅瓧  鎻忚堪"锛?
    getline(file, line); 

    int id;
    string name, desc;
    // 浣跨敤 >> 鑳藉鑷姩璺宠繃鏂囦欢閲岀殑鎵€鏈夌殑绌烘牸鍜孴ab
    while (file >> id >> name >> desc) {
        Scene s = {id, name, desc};
        g.scenes[id] = s;  // 鎶婅鍒扮殑鏁版嵁鏀捐繘浼犺繘鏉ョ殑 g 閲岄潰
    }
    file.close();
    return true;
}

bool deleteScene(Graph& g, int id) {
    // 鐩存帴鎿嶄綔 g.scenes 鍜?g.adjList
    if (g.scenes.find(id) == g.scenes.end()) return false;
    g.scenes.erase(id);
    g.adjList.erase(id);
    // ... 鍏朵粬鍓旈櫎杈圭殑閫昏緫
    return true;
}