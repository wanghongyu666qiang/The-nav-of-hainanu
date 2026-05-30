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
        cout<<"2. 查询所有路径"<<endl;
        cout<<"3. 查看景点信息"<<endl;
        cout<<"4. 输入景点代码查到其它景点的最短距离"<<endl;
        cout<<"5. 增加景点"<<endl;
        cout<<"6. 删除景点"<<endl;
        cout<<"7. 修改景点"<<endl;
        cout<<"8. 增加道路"<<endl;
        cout<<"9. 删除道路"<<endl;
        cout<<"10. 修改道路"<<endl;
        cout<<"11. 退出系统"<<endl;
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
        printScenes(g);
        cout<<"请输入起点和终点的编号：";
        int sid, eid; cin>>sid>>eid;
        int si=getIdIndex(g.scenes,sid), ei=getIdIndex(g.scenes,eid);
        if(si==-1||ei==-1){
            cout<<"编号不存在！"<<endl;
        }else{
            findAllPaths(g,si,ei);
        }
        break;
    }
    case 3:{
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
    case 4:{
        cout<<"请输入景点编号：";
        int id;
        cin>>id;
        int index=getIdIndex(g.scenes,id);
        if(index==-1){
            cout<<"景点编号不存在！"<<endl;
        }else{
            cout<<"请输入用户类型(0步行,1车行)：";
            int userType;
            cin>>userType;
            Graph graphToUse=getFilteredGraph(g,userType);
            for(int i=0;i<graphToUse.scenes.size();i++){
                if(i==index) continue;
                cout<<"从"<<g.scenes[index].name<<"到"<<g.scenes[i].name<<"的最短路径："<<endl;
                getshortestpath(graphToUse,index,i,userType);
            }
        }
        break;
    }
    case 5:{
        cout<<"请输入新景点的编号、名称和描述：";
        int id; string name, desc;
        cin>>id>>name>>desc;
        if(addScene(g,id,name,desc))
            cout<<"景点添加成功！"<<endl;
        else
            cout<<"景点添加失败！可能是编号已存在。"<<endl;
        break;
    }
    case 6:{
        cout<<"请输入要删除的景点编号：";
        int id; cin>>id;
        if(deleteScene(g,id))
            cout<<"景点删除成功！"<<endl;
        else
            cout<<"景点删除失败！可能是编号不存在。"<<endl;
        break;
    }
    case 7:{
        cout<<"请输入要修改的景点编号：";
        int id; cin>>id;
        int index=getIdIndex(g.scenes,id);
        if(index==-1){
            cout<<"景点编号不存在！"<<endl;
        }else{
            cout<<"请输入新的名称和描述：";
            string name,desc; cin>>name>>desc;
            g.scenes[index].name=name;
            g.scenes[index].description=desc;
            saveScenes(g,"data/scene.txt");
            cout<<"景点修改成功！"<<endl;
        }
        break;
    }
    case 8:{
        cout<<"请输入道路的起点编号、终点编号、权重和类型(0步行,1车行)：";
        int from,to,weight,type; cin>>from>>to>>weight>>type;
        if(addRoad(g,from,to,weight,type))
            cout<<"道路添加成功！"<<endl;
        else
            cout<<"道路添加失败！"<<endl;
        break;
    }
    case 9:{
        cout<<"请输入要删除道路的起点和终点编号：";
        int from,to; cin>>from>>to;
        if(deleteRoad(g,from,to))
            cout<<"道路删除成功！"<<endl;
        else
            cout<<"道路删除失败！"<<endl;
        break;
    }
    case 10:{
        cout<<"请输入要修改道路的起点和终点编号：";
        int from,to; cin>>from>>to;
        int fi=getIdIndex(g.scenes,from),ti=getIdIndex(g.scenes,to);
        if(fi==-1||ti==-1){
            cout<<"编号不存在！"<<endl;
        }else{
            cout<<"请输入新的权重和类型(0步行,1车行)：";
            int weight,type; cin>>weight>>type;
            g.scenes[fi].edges[ti]={to,weight,type};
            g.scenes[ti].edges[fi]={from,weight,type};
            saveRoads(g,"data/road.txt");
            cout<<"道路修改成功！"<<endl;
        }
        break;
    }
    case 11:{
        cout<<"感谢使用，再见！"<<endl;
        return 0;
}
  }
}
}