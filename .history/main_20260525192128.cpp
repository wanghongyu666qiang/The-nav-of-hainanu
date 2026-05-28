#include <iostream>
#include <vector>
#include "algorithm/Graph.h"

using namespace std;

int main() {
    CampusGraph graph;

    //  初始化数据 (务必确认txt路径正确)
    if (!graph.loadScenes("data/scene.txt") || !graph.loadRoads("data/road.txt")) {
        cout << "数据加载失败！" << endl;
        return 1;
    }
    cout << "地图数据加载成功！" << endl;

    // 测试
    int start = 1; // 1: 东大门
    int end = 5;   // 5: 思源学堂
    
    cout << "\n测试行人寻路 (由 1 去 5):" << endl;
    vector<int> path = graph.getShortestPath(start, end, 1);
    
    cout << "路线: ";
    for (int id : path) {
        cout << graph.getSceneName(id) << " -> ";
    }
    cout << "结束" << endl;

    return 0;
}