#include "Graph.h"
#include <fstream>
#include <iostream>

using namespace std;

// 杩欓噷鍙啓 CampusGraph 绫婚噷璺熷啓鏂囦欢鍜屾敼鏁版嵁鏈夌殑鍑芥暟

bool CampusGraph::saveScenesToFile(const std::string& filename) {
    ofstream file(filename); 
    if (!file.is_open()) return false;
    for (const auto& pair : scenes) {
        const Scene& s = pair.second;
        file << s.id << "," << s.name << "," << s.x << "," 
             << s.y << "," << s.description << "\n";
    }
    file.close();
    return true;
}

bool CampusGraph::deleteScene(int id) {
    // 浣犵殑鍒犻櫎缁撶偣閫昏緫锛岃寰楀湪寮€澶村姞涓? bool CampusGraph:: 鍓嶇紑
    // ......
}

// ... 鎺ョ潃鍐?updateScene, addRoad 绛夌瓑