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
        // 鍒濆鍖栨椂鍖呭惈绌虹殑 walkEdges 鍜?driveEdges
        Scene s = {id, name, desc, vector<Edge>(), vector<Edge>()};
        g.scenes.push_back(s);  // 鐩存帴鏀惧叆鏁扮粍
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
        for (Scene& s : g.scenes) {
            if (s.id == from) {
                if (type == 0) s.walkEdges.push_back({to, weight, type});
                else s.driveEdges.push_back({to, weight, type});
            }
            if (s.id == to) {
                if (type == 0) s.walkEdges.push_back({from, weight, type});
                else s.driveEdges.push_back({from, weight, type});
            }
        }
    }
    file.close();
    return true;
}

// 3. 灏嗗唴瀛橀噷鐨勬櫙鐐规暟鎹啓鍥炴枃浠讹紙鎸佷箙鍖栵級
bool saveScenes(const Graph& g, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) return false;

    file << "缂栧彿\t鍚嶅瓧\t鎻忚堪\n"; // 鍐欏叆琛ㄥご
    for (const Scene& s : g.scenes) {
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
    for (const Scene& s : g.scenes) {
        int from = s.id;
        for (const Edge& e : s.edges) {
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
    for (const Scene& s : g.scenes) {
        if (s.id == id) return false;
    }
    
    g.scenes.push_back({id, name, desc, vector<Edge>()});
    // 寮哄埗淇濆瓨鍒版枃浠?
    saveScenes(g, "data/scene.txt");
    return true;
}

// 鍒犻櫎鏅偣
bool deleteScene(Graph& g, int id) {
    bool found = false;

    auto it = g.scenes.begin();
    while (it != g.scenes.end()) {
        if (it->id == id) {
            // 鎵惧埌鏅偣鏈韩锛屽交搴曞垹闄?
            it = g.scenes.erase(it);
            found = true;
        } else {
            // 鍒犻櫎鍏朵粬鏅偣閫氬悜璇d鐨勮竟
            auto& edges = it->edges;
            auto edgeIt = edges.begin();
            while (edgeIt != edges.end()) {
                if (edgeIt->to == id) {
                    edgeIt = edges.erase(edgeIt);
                } else {
                    ++edgeIt;
                }
            }
            ++it;
        }
    }

    if (!found) return false;

    // 鏇存柊鏂囦欢
    saveScenes(g, "data/scene.txt");
    saveRoads(g, "data/road.txt");
    return true;
}

// 淇敼鏅偣
bool updateScene(Graph& g, int id, string name, string desc) {
    for (Scene& s : g.scenes) {
        if (s.id == id) {
            s.name = name;
            s.description = desc;
            saveScenes(g, "data/scene.txt");
            return true;
        }
    }
    return false;
}

// 澧炲姞杩炴帴杈癸紙閬撹矾锛?
bool addRoad(Graph& g, int from, int to, int weight, int type) {
    bool fromFound = false, toFound = false;
    for (const Scene& s : g.scenes) {
        if (s.id == from) fromFound = true;
        if (s.id == to) toFound = true;
    }
    // 妫€鏌ヨ捣鐐瑰拰缁堢偣鏄惁瀛樺湪
    if (!fromFound || !toFound) return false;

    for (Scene& s : g.scenes) {
        if (s.id == from) {
            bool dup = false;
            for (const auto& e : s.edges) if (e.to == to) dup = true;
            if (!dup) s.edges.push_back({to, weight, type});
        }
        if (s.id == to) {
            bool dup = false;
            for (const auto& e : s.edges) if (e.to == from) dup = true;
            if (!dup) s.edges.push_back({from, weight, type});
        }
    }
    
    saveRoads(g, "data/road.txt");
    return true;
}

// 鍒犻櫎杩炴帴杈癸紙閬撹矾锛?
bool deleteRoad(Graph& g, int from, int to) {
    bool found = false;
    
    for (Scene& s : g.scenes) {
        if (s.id == from) {
            auto it = s.edges.begin();
            while (it != s.edges.end()) {
                if (it->to == to) {
                    it = s.edges.erase(it);
                    found = true;
                } else {
                    ++it;
                }
            }
        }
        if (s.id == to) {
            auto it = s.edges.begin();
            while (it != s.edges.end()) {
                if (it->to == from) {
                    it = s.edges.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }

    if (found) saveRoads(g, "data/road.txt");
    return found;
}

// 淇敼杈癸紙閲嶆柊璁剧疆鏉冮噸/绫诲瀷锛?
bool updateRoad(Graph& g, int from, int to, int weight, int type) {
    bool found = false;
    
    for (Scene& s : g.scenes) {
        if (s.id == from) {
            for (Edge& e : s.edges) {
                if (e.to == to) {
                    e.weight = weight;
                    e.roadType = type;
                    found = true;
                }
            }
        }
        if (s.id == to) {
            for (Edge& e : s.edges) {
                if (e.to == from) {
                    e.weight = weight;
                    e.roadType = type;
                    found = true;
                }
            }
        }
    }

    if (found) saveRoads(g, "data/road.txt");
    return found;
}