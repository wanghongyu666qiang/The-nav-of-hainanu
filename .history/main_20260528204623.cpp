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
    case 1: getshortestpath(g); break;
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