#include "../Graph.h"
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
        // 鍒濆鍖栨椂鍖呭惈绌?vector<Edge>()
        Scene s = {id, name, desc, vector<Edge>()};
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
            if (s.id == from) s.edges.push_back({to, weight, type});
            if (s.id == to) s.edges.push_back({from, weight, type});
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

// 鎻愬彇鍑鸿璧颁笓鐢ㄧ殑閭绘帴鐭╅樀鍥撅紝渚涚畻娉曚娇鐢?
Graph getWalkGraph(const Graph& g) {
    Graph res = g;
    // 鏋勫缓閭绘帴鐭╅樀褰㈠紡鐨?edges 閰嶅悎 Dijkstra 鐨勭储寮曡闂?
    for (int i = 0; i < res.scenes.size(); ++i) {
        vector<Edge> matrixEdges(res.scenes.size());
        for (int j = 0; j < res.scenes.size(); ++j) {
            matrixEdges[j] = {res.scenes[j].id, INT_MAX, 0}; 
        }
        matrixEdges[i].weight = 0; // 鑷韩鍒拌嚜韬窛绂讳负 0
        
        for (const Edge& e : g.scenes[i].edges) {
            if (e.roadType == 0) { // 浠呮彁鍙栦汉琛岄亾
                int targetIndex = -1;
                for (int k = 0; k < res.scenes.size(); ++k) {
                    if (res.scenes[k].id == e.to) {
                        targetIndex = k;
                        break;
                    }
                }
                if (targetIndex != -1) {
                    matrixEdges[targetIndex].weight = e.weight;
                }
            }
        }
        res.scenes[i].edges = matrixEdges;
    }
    return res;
}

// 鎻愬彇鍑鸿溅琛屼笓鐢ㄧ殑閭绘帴鐭╅樀鍥撅紝渚涚畻娉曚娇鐢?
Graph getDriveGraph(const Graph& g) {
    Graph res = g;
    for (int i = 0; i < res.scenes.size(); ++i) {
        vector<Edge> matrixEdges(res.scenes.size());
        for (int j = 0; j < res.scenes.size(); ++j) {
            matrixEdges[j] = {res.scenes[j].id, INT_MAX, 1}; 
        }
        matrixEdges[i].weight = 0; 
        
        for (const Edge& e : g.scenes[i].edges) {
            if (e.roadType == 1) { // 浠呮彁鍙栬溅閬?
                int targetIndex = -1;
                for (int k = 0; k < res.scenes.size(); ++k) {
                    if (res.scenes[k].id == e.to) {
                        targetIndex = k;
                        break;
                    }
                }
                if (targetIndex != -1) {
                    matrixEdges[targetIndex].weight = e.weight;
                }
            }
        }
        res.scenes[i].edges = matrixEdges;
    }
    return res;
}
