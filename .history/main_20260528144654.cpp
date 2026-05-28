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

    // 交互菜单
    while (true) {
        cout << "\n=== 海南大学导航系统 ===" << endl;
        cout << "1. 查询最短路径" << endl;
        cout << "2. 退出系统" << endl;
        cout << "请输入您的选择: ";
        
        int choice;
        cin >> choice;

        if (choice == 1) {
            int start, end, type;
            cout << "请输入起点编号: ";
            cin >> start;
            cout << "请输入终点编号: ";
            cin >> end;
            cout << "请输入出行方式 (0代表步行, 1代表车行): ";
            cin >> type;

            vector<int> path;
            if (type == 0) {
                path = getShortestPath(walkGraph, start, end, 0);
            } else {
                path = getShortestPath(driveGraph, start, end, 1);
            }

            cout << "最短路径包含的节点: ";
            for (int i = 0; i < path.size(); i++) {
                cout << path[i] << " ";
            }
            cout << endl;
        } else if (choice == 2) {
            cout << "成功退出系统！" << endl;
            break;
        } else {
            cout << "输入有误，请重新输入！" << endl;
        }
    }

    return 0;
}