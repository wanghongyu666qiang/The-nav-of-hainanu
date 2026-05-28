#include <iostream>
#include "algorithm/Graph.h"

using namespace std;

int main() {
    // 1. 声明一个包含了景点和边的图变量
    Graph myGraph; 

    // 2. 调用函数把数据读进去 (把 myGraph 作为参数传进去填满)
    if (!loadScenes(myGraph, "data/scene.txt")) {
        cout << "【严重错误】无法读取 data/scene.txt！请确保您在项目的根目录运行程序，而不是 output 文件夹。" << endl;
        system("pause");
        return -1;
    }
    if (!loadRoads(myGraph, "data/road.txt")) {
        cout << "【严重错误】无法读取 data/road.txt！" << endl;
        system("pause");
        return -1;
    }

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

            // 由于景点 ID 是用户输入的（1~10），而 getShortestPath 是基于数组下标（0~9）计算的
            // 所以我们需要将传入的 ID 转换为数组索引进行计算，完成后再把结果转换回真实 ID！
            int startIndex = -1, endIndex = -1;
            for (int i = 0; i < myGraph.scenes.size(); i++) {
                if (myGraph.scenes[i].id == start) startIndex = i;
                if (myGraph.scenes[i].id == end) endIndex = i;
            }

            if (startIndex == -1 || endIndex == -1) {
                cout << "您输入的景点编号不存在，请重新输入！" << endl;
                continue;
            }

            vector<int> path;
            if (type == 0) {
                path = getShortestPath(walkGraph, startIndex, endIndex, 0);
            } else {
                path = getShortestPath(driveGraph, startIndex, endIndex, 1);
            }

            if (path.empty() || path[0] == -1) {
                cout << "抱歉，无法找到从起点到终点的该种出行类型路径！" << endl;
            } else {
                cout << "最短路径包含的节点: ";
                for (int i = 0; i < path.size(); i++) {
                    // 结果是从 path 里出来的索引，要转回景点的真实 ID
                    cout << myGraph.scenes[path[i]].id << (i == path.size() - 1 ? "" : " -> ");
                }
                cout << endl;
            }
        } else if (choice == 2) {
            cout << "成功退出系统！" << endl;
            break;
        } else {
            cout << "输入有误，请重新输入！" << endl;
        }
    }

    return 0;
}