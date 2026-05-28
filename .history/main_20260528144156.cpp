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
    
    // 4. 将总表解耦成人行道和车道
    Graph walkGraph = getWalkGraph(myGraph);
    Graph driveGraph = getDriveGraph(myGraph);

    // 5. 测试算法（传入解耦好的专用图，确保以原本的 Dijkstra 算法代码为中心，不需要修改它）
    // 假设 userType=0 代表步行，userType=1 代表车行（最后那个 0/1 参数原本没用到，所以我们通过传入不同的专用图来实现解耦）
    vector<int> pathWalk = getShortestPath(walkGraph, 1, 4, 0);
    vector<int> pathDrive = getShortestPath(driveGraph, 1, 4, 1);

    cout << "程序运行成功完成！" << endl;
    system("pause"); // 如果使用外部控制台，防止窗口一闪而过

    return 0;
}