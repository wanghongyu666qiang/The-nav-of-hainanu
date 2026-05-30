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
    while (file >> id >> name >> desc) {
        // 鍏堝缓绔嬬┖鐨?edges
        Scene s = {id, name, desc, vector<Edge>()};
        g.scenes.push_back(s);
    }
    file.close();

    // 鍦ㄨ鍙栧畬鎵€鏈夋櫙鐐瑰悗锛屽垵濮嬪寲姣忎釜鏅偣鐨勯偦鎺ョ煩闃垫暟鎹粨鏋?
    int n = g.scenes.size();
    for (int i = 0; i < n; ++i) {
        g.scenes[i].edges = vector<Edge>(n);
        for (int j = 0; j < n; ++j) {
            // 鐢ㄦ瘡涓綅缃搴旂殑鏅偣 ID 濉厖 to 瀛楁锛屾潈閲嶅垵濮嬪寲涓?INT_MAX
            g.scenes[i].edges[j] = {g.scenes[j].id, INT_MAX, -1};
        }
        // 鑷繁鍒拌嚜宸辩殑璺濈涓?0
        g.scenes[i].edges[i].weight = 0;
    }
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
        // 鍥犱负鏄偦鎺ョ煩闃碉紝鎴戜滑闇€瑕侀€氳繃 ID 鎵惧埌瀵瑰簲鐨勭储寮?
        int fromIndex = -1, toIndex = -1;
        for (int i = 0; i < g.scenes.size(); ++i) {
            if (g.scenes[i].id == from) fromIndex = i;
            if (g.scenes[i].id == to) toIndex = i;
        }

        // 鍙屽悜璧嬪€硷紙瑕嗙洊鍘熸湰鐨?INT_MAX锛?
        if (fromIndex != -1 && toIndex != -1) {
            g.scenes[fromIndex].edges[toIndex].weight = weight;
            g.scenes[fromIndex].edges[toIndex].roadType = type;
            
            g.scenes[toIndex].edges[fromIndex].weight = weight;
            g.scenes[toIndex].edges[fromIndex].roadType = type;
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
    for (int i = 0; i < g.scenes.size(); ++i) {
        for (int j = i + 1; j < g.scenes.size(); ++j) {
            // 鍙涓嶆槸鏃犵┓澶э紝涓斾笉鏄嚜韬紝璇存槑鏈変竴鏉¤矾
            if (g.scenes[i].edges[j].weight!=INT_MAX) {
                file<<g.scenes[i].id<<"\t" 
                    <<g.scenes[j].id<<"\t" 
                    <<g.scenes[i].edges[j].weight << "\t" 
                    <<g.scenes[i].edges[j].roadType << "\n";
            }
        }
    }
    file.close();
    return true;
}




// 鎻愬彇鍑鸿璧颁笓鐢ㄧ殑閭绘帴鐭╅樀鍥撅紝渚涚畻娉曚娇鐢?
Graph getWalkGraph(const Graph& g) {
    Graph res = g;
    int n = (int)res.scenes.size();
    for (int i = 0; i < n; ++i) {
        vector<Edge> matrixEdges(n);
        for (int j = 0; j < n; ++j) matrixEdges[j] = {res.scenes[j].id, INT_MAX, 0};
        matrixEdges[i].weight = 0;
        for (const Edge& e : g.scenes[i].edges) {
            if (e.roadType == 0) {
                int targetIndex = -1;
                for (int k = 0; k < n; ++k) if (res.scenes[k].id == e.to) { targetIndex = k; break; }
                if (targetIndex != -1) matrixEdges[targetIndex].weight = e.weight;
            }
        }
        res.scenes[i].edges = matrixEdges;
    }
    return res;
}



// 鎻愬彇鍑鸿溅琛屼笓鐢ㄧ殑閭绘帴鐭╅樀鍥撅紝渚涚畻娉曚娇鐢?
Graph getDriveGraph(const Graph& g) {
    Graph res = g;
    int n = (int)res.scenes.size();
    for (int i = 0; i < n; ++i) {
        vector<Edge> matrixEdges(n);
        for (int j = 0; j < n; ++j) matrixEdges[j] = {res.scenes[j].id, INT_MAX, 1};
        matrixEdges[i].weight = 0;
        for (const Edge& e : g.scenes[i].edges) {
            if (e.roadType == 1) {
                int targetIndex = -1;
                for (int k = 0; k < n; ++k) if (res.scenes[k].id == e.to) { targetIndex = k; break; }
                if (targetIndex != -1) matrixEdges[targetIndex].weight = e.weight;
            }
        }
        res.scenes[i].edges = matrixEdges;
    }
    return res;
}
