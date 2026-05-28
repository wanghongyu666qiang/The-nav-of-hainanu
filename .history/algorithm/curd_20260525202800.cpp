#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// 注意参数里有 Graph& g
bool loadScenes(Graph& g, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    string line;
    // 先读一行废弃掉（因为你第一行是中文表头："编号  名字  描述"）
    getline(file, line); 

    int id;
    string name, desc;
    // 使用 >> 能够自动跳过文件里的所有的空格和Tab
    while (file >> id >> name >> desc) {
        Scene s = {id, name, desc};
        g.scenes[id] = s;  // 把读到的数据放进传进来的 g 里面
    }
    file.close();
    return true;
}

bool deleteScene(Graph& g, int id) {
    // 直接操作 g.scenes 和 g.adjList
    if (g.scenes.find(id) == g.scenes.end()) return false;
    g.scenes.erase(id);
    g.adjList.erase(id);
    // ... 其他剔除边的逻辑
    return true;
}