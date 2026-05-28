#include <iostream>
#include "algorithm/Graph.h"

using namespace std;

int main() {
    // 1. 声明一个包含了景点和边的图变量
    Graph myGraph; 

    // 2. 调用函数把数据读进去 (把 myGraph 作为参数传进去填满)
    loadScenes(myGraph, "data/scene.txt");
    loadRoads(myGraph, "data/road.txt");

    // 3. 测试增删改查
    addScene(myGraph, 6, "宿舍楼", "睡觉的地方");
    
    // 4. 测试算法
    vector<int> path = getShortestPath(myGraph, 1, 4, 1);

    return 0;
}