#include <iostream>
#include "algorithm/Graph.h"
using namespace std;

int main() {
    Graph g;
    loadScenes(g, "data/scene.txt");
  while(true) {
        cout<<"欢迎使用海南大学导航系统！"<<endl;
        cout<<"1. 查询最短路径"<<endl;
        cout<<"2. 增加景点"<<endl;
        cout<<"3. 删除景点"<<endl;
        cout<<"4. 修改景点"<<endl;
        cout<<"5. 增加道路"<<endl;
        cout<<"6. 删除道路"<<endl;
        cout<<"7. 修改道路"<<endl;
        cout<<"8. 退出系统"<<endl;
cout<<"请输入操作编号：";
int choice;
cin>>choice;
switch(choice){
    case 1: {
        printScenes(g);
        cout << "请输入起点和终点的编号以及用户类型(0步行,1车行)：";
        int startId, endId, userType;
        cin >> startId >> endId >> userType;

        // 这里将用户输入的 ID 原本转成了 index，然后在算法外部使用
        int startIndex = -1, endIndex = -1;
        for (int i = 0; i < g.scenes.size(); i++) {
            if (g.scenes[i].id == startId) startIndex = i;
            if (g.scenes[i].id == endId) endIndex = i;
        }

        if (startIndex == -1 || endIndex == -1) {
            cout << "输入的景点编号不存在！" << endl;
        } else {
            // 生成对应通行权限的图并传给原封不动的算法
            Graph graphToUse = (userType == 0) ? getWalkGraph(g) : getDriveGraph(g);
            getshortestpath(graphToUse, startIndex, endIndex, userType);
        }
        break;
    }
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        cout<<"感谢使用，再见！"<<endl;
        return 0;
}
  }
}