#include <iostream>
#include "algorithm/Graph.h"
using namespace std;

int main() {
    Graph g;
    if (!loadScenes(g, "data/scene.txt")) {
        cout << "景点数据加载失败！" << endl;
        return 1;
    }
    if (!loadRoads(g, "data/road.txt")) {
        cout << "道路数据加载失败！" << endl;
        return 1;
    }
  while(true) {
        cout<<"欢迎使用海南大学导航系统！"<<endl;
        cout<<"1. 查询最短路径"<<endl;
        cout<<"2. 查看景点信息"<<endl;
        cout<<"3. 输入景点代码查到其它景点的最短距离"<<endl;
        cout<<"4. 增加景点"<<endl;
        cout<<"5. 删除景点"<<endl;
        cout<<"6. 修改景点"<<endl;
        cout<<"7. 增加道路"<<endl;
        cout<<"8. 删除道路"<<endl;
        cout<<"9. 修改道路"<<endl;
        cout<<"10. 退出系统"<<endl;
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
        int startIndex = getIdIndex(g.scenes, startId);
        int endIndex = getIdIndex(g.scenes, endId);

        if (startIndex == -1 || endIndex == -1) {
            cout << "输入的景点编号不存在！" << endl;
        } else {
            // 生成对应通行权限的图并传给原封不动的算法
            Graph graphToUse = getFilteredGraph(g, userType);
            getshortestpath(graphToUse, startIndex, endIndex, userType);
        }
        break;
    }
    case 2:{
      cout<<"请输入景点编号：";
      int id;
      cin>>id;
        int index=getIdIndex(g.scenes,id);//得到在图中的位置
        if(index==-1){
            cout<<"景点编号不存在！"<<endl;
        }
        else{
            cout<<"景点名称："<<g.scenes[index].name<<endl;
            cout<<"景点描述："<<g.scenes[index].description<<endl;
        }
        break;
    }
    case 3:{
        cout<<"请输入景点编号：";
        int id;
        cin>>id;
        int index=getIdIndex(g.scenes,id);//得到在图中的位置
        cout<<"请输入用户类型(0步行,1车行)：";
        int userType;
        cin>>userType;
Graph graphtouse=getFilteredGraph(g,userType);
    for(int i=0;i<graphtouse.scenes.size();i++){
        if(i==index) continue;//不需要算自己到自己的距离
        cout<<"从"<<g.scenes[index].name<<"到"<<g.scenes[i].name<<"的最短路径："<<endl;
        getshortestpath(graphtouse,index,i,userType);
    }
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10: {
        cout<<"感谢使用，再见！"<<endl;
        return 0;
}
  }
}
}