#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// 1. 浠庢枃浠惰鍙栨櫙鐐规暟鎹?
bool loadScenes(Graph& g, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    string line;
    // 鍏堣涓€琛屽簾寮冩帀锛堝洜涓虹涓€琛屾槸涓枃琛ㄥご锛?缂栧彿  鍚嶅瓧  鎻忚堪"锛?
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

// 2. 浠庢枃浠惰鍙栭亾璺暟鎹?
bool loadRoads(Graph& g, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    string line;
    // 鍏堣涓€琛屽簾寮冩帀琛ㄥご锛?璧风偣  缁堢偣  璺濈  绫诲瀷"锛?
    getline(file, line); 

    int from, to, weight, type;
    while (file >> from >> to >> weight >> type) {
        // 鍙屽悜閬撹矾锛屼袱杈归兘瑕佸姞
        g.adjList[from].push_back({to, weight, type});
        g.adjList[to].push_back({from, weight, type});
    }
    file.close();
    return true;
}

// 3. 灏嗗唴瀛橀噷鐨勬櫙鐐规暟鎹啓鍥炴枃浠讹紙鎸佷箙鍖栵級
bool saveScenes(const Graph& g, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) return false;

    file << "缂栧彿\t鍚嶅瓧\t鎻忚堪\n"; // 鍐欏叆琛ㄥご
    for (const auto& pair : g.scenes) {
        const Scene& s = pair.second;
        file << s.id << "\t" << s.name << "\t" << s.description << "\n";
    }
    file.close();
    return true;
}

// 4. 灏嗗唴瀛橀噷鐨勯亾璺暟鎹啓鍥炴枃浠讹紙鎸佷箙鍖栵級
bool saveRoads(const Graph& g, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) return false;

    file << "璧风偣\t缁堢偣\t璺濈\t绫诲瀷\n"; // 鍐欏叆琛ㄥご
    // 涓轰簡闃叉鍙屽悜杈瑰啓鍏ヤ袱娆★紝鍙互鐢ㄤ簩缁磎ap鎴栧彧鍦?from < to 鏃跺啓鍏?
    for (const auto& pair : g.adjList) {
        int from = pair.first;
        for (const Edge& e : pair.second) {
            if (from < e.to) { // 瑙ｅ喅鏃犲悜鍥鹃噸澶嶅啓鍏ョ殑闂
                file << from << "\t" << e.to << "\t" << e.weight << "\t" << e.roadType << "\n";
            }
        }
    }
    file.close();
    return true;
}

// ================== C U R D (澧炲垹鏀规煡) 涓氬姟浠ｇ爜 ==================

// 澧炲姞鏅偣
bool addScene(Graph& g, int id, string name, string desc) {
    // 妫€鏌ユ槸鍚﹀凡缁忓瓨鍦?
    if (g.scenes.find(id) != g.scenes.end()) return false; 
    
    g.scenes[id] = {id, name, desc};
    // 寮哄埗淇濆瓨鍒版枃浠?
    saveScenes(g, "data/scene.txt");
    return true;
}

// 鍒犻櫎鏅偣
bool deleteScene(Graph& g, int id) {
    if (g.scenes.find(id) == g.scenes.end()) return false;

    // 1. 鍒犻櫎鏅偣淇℃伅
    g.scenes.erase(id);

    // 2. 鍒犻櫎涓庤鏅偣鐩存帴鐩稿叧鐨勯偦鎺ラ摼琛?
    g.adjList.erase(id);

    // 3. 閬嶅巻鍏朵粬鎵€鏈夋櫙鐐圭殑閾捐〃锛屽垹闄ら€氬悜杩欎釜 id 鐨勮竟
    for (auto& pair : g.adjList) {
        vector<Edge>& edges = pair.second;
        for (auto it = edges.begin(); it != edges.end(); ) {
            if (it->to == id) {
                it = edges.erase(it);
            } else {
                ++it;
            }
        }
    }

    // 鏇存柊鏂囦欢
    saveScenes(g, "data/scene.txt");
    saveRoads(g, "data/road.txt");
    return true;
}

// 淇敼鏅偣
bool updateScene(Graph& g, int id, string name, string desc) {
    if (g.scenes.find(id) == g.scenes.end()) return false;
    
    g.scenes[id].name = name;
    g.scenes[id].description = desc;
    
    saveScenes(g, "data/scene.txt");
    return true;
}

// 澧炲姞杩炴帴杈癸紙閬撹矾锛?
bool addRoad(Graph& g, int from, int to, int weight, int type) {
    // 妫€鏌ヨ捣鐐瑰拰缁堢偣鏄惁瀛樺湪
    if (g.scenes.find(from) == g.scenes.end() || g.scenes.find(to) == g.scenes.end()) {
        return false;
    }

    // 妫€鏌ユ槸鍚﹀凡缁忔湁杩欐潯杈癸紙闃叉閲嶅娣诲姞锛?
    for (const Edge& e : g.adjList[from]) {
        if (e.to == to) return false;
    }

    g.adjList[from].push_back({to, weight, type});
    g.adjList[to].push_back({from, weight, type}); // 鏃犲悜鍥?
    
    saveRoads(g, "data/road.txt");
    return true;
}

// 鍒犻櫎杩炴帴杈癸紙閬撹矾锛?
bool deleteRoad(Graph& g, int from, int to) {
    bool found = false;
    
    // 浠?from 鐨勯摼琛ㄤ腑鍒犻櫎 to
    auto& fromEdges = g.adjList[from];
    for (auto it = fromEdges.begin(); it != fromEdges.end(); ) {
        if (it->to == to) {
            it = fromEdges.erase(it);
            found = true;
        } else {
            ++it;
        }
    }
    
    // 浠?to 鐨勯摼琛ㄤ腑鍒犻櫎 from
    auto& toEdges = g.adjList[to];
    for (auto it = toEdges.begin(); it != toEdges.end(); ) {
        if (it->to == from) {
            it = toEdges.erase(it);
        } else {
            ++it;
        }
    }

    if (found) saveRoads(g, "data/road.txt");
    return found;
}

// 淇敼杈癸紙閲嶆柊璁剧疆鏉冮噸/绫诲瀷锛?
bool updateRoad(Graph& g, int from, int to, int weight, int type) {
    bool found = false;
    
    for (Edge& e : g.adjList[from]) {
        if (e.to == to) {
            e.weight = weight;
            e.roadType = type;
            found = true;
            break;
        }
    }
    for (Edge& e : g.adjList[to]) {
        if (e.to == from) {
            e.weight = weight;
            e.roadType = type;
            found = true;
            break;
        }
    }

    if (found) saveRoads(g, "data/road.txt");
    return found;
}