#include "Graph.h"
#include <fstream>
#include <iostream>

using namespace std;

// 这里只写 CampusGraph 类里跟写文件和改数据有的函数

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
    // 你的删除结点逻辑，记得在开头加上  bool CampusGraph:: 前缀
    // ......
}

// ... 接着写 updateScene, addRoad 等等