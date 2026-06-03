#include<iostream>
#include "algorithm/Graph.h"
using namespace std;

int main(){
Graph gWalk,gCar;
if(!loadScenes(gWalk,"data/scene.txt")){
cout<<"景点数据加载失败！"<<endl;
return 1;
}
if(!loadScenes(gCar,"data/scene.txt")){
cout<<"景点数据加载失败！"<<endl;
return 1;
}
if(!loadRoads(gWalk,"data/road.txt",0)){
cout<<"步行道路加载失败！"<<endl;
return 1;
}
if(!loadRoads(gCar,"data/road.txt",1)){
cout<<"车行道路加载失败！"<<endl;
return 1;
}
while(true){
    cout<<"------------------------------"<<endl;
cout<<"欢迎使用海南大学导航系统！"<<endl;
cout<<"0. 打开交互式地图"<<endl;
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
case 0:{
cout<<"未引入前端模块。请使用控制台功能。"<<endl;
break;
}
case 1:{
printScenes(gWalk);
cout<<"请输入起点和终点的编号以及用户类型(0步行,1车行)：";
int startId,endId,userType;
cin>>startId>>endId>>userType;
int startIndex=getIdIndex(gWalk.scenes,startId);
int endIndex=getIdIndex(gWalk.scenes,endId);
if(startIndex==-1||endIndex==-1){
cout<<"输入的景点编号不存在！"<<endl;
}else{
const Graph& active=(userType==0)?gWalk:gCar;
getshortestpath(active,startIndex,endIndex,userType);
}
break;
}
case 2:{
printScenes(gWalk);
cout<<"请输入起点和终点的编号：";
int sid,eid;cin>>sid>>eid;
int si=getIdIndex(gWalk.scenes,sid);
int ei=getIdIndex(gWalk.scenes,eid);
if(si==-1||ei==-1){
cout<<"编号不存在！"<<endl;
}else{
findAllPaths(gWalk,si,ei);
}
break;
}
case 3:{
cout<<"请输入景点编号：";
int id;cin>>id;
int index=getIdIndex(gWalk.scenes,id);
if(index==-1){
cout<<"景点编号不存在！"<<endl;
}else{
cout<<"景点名称："<<gWalk.scenes[index].name<<endl;
cout<<"景点描述："<<gWalk.scenes[index].description<<endl;
}
break;
}
case 4:{
cout<<"请输入景点编号：";
int id;cin>>id;
int index=getIdIndex(gWalk.scenes,id);
if(index==-1){
cout<<"景点编号不存在！"<<endl;
}else{
cout<<"请输入用户类型(0步行,1车行)：";
int userType;cin>>userType;
const Graph& active=(userType==0)?gWalk:gCar;
for(int i=0;i<(int)active.scenes.size();i++){
if(i==index) continue;
cout<<"从"<<gWalk.scenes[index].name<<"到"<<gWalk.scenes[i].name<<"的最短路径："<<endl;
getshortestpath(active,index,i,userType);
}
}
break;
}
case 5:{
cout<<"请输入新景点的编号、名称和描述：";
int id;string name,desc;
cin>>id>>name>>desc;
if(addScene(gWalk,id,name,desc)&&addScene(gCar,id,name,desc)){
saveScenes(gWalk,"data/scene.txt");
cout<<"景点添加成功！"<<endl;
}else{
cout<<"景点添加失败！可能是编号已存在。"<<endl;
}
break;
}
case 6:{
cout<<"请输入要删除的景点编号：";
int id;cin>>id;
if(deleteScene(gWalk,id)&&deleteScene(gCar,id)){
saveScenes(gWalk,"data/scene.txt");
saveAllRoads(gWalk,gCar,"data/road.txt");
cout<<"景点删除成功！"<<endl;
}else{
cout<<"景点删除失败！可能是编号不存在。"<<endl;
}
break;
}
case 7:{
cout<<"请输入要修改的景点编号：";
int id;cin>>id;
int index=getIdIndex(gWalk.scenes,id);
if(index==-1){
cout<<"景点编号不存在！"<<endl;
}else{
cout<<"请输入新的名称和描述：";
string name,desc;cin>>name>>desc;
gWalk.scenes[index].name=name;
gWalk.scenes[index].description=desc;
gCar.scenes[index].name=name;
gCar.scenes[index].description=desc;
saveScenes(gWalk,"data/scene.txt");
cout<<"景点修改成功！"<<endl;
}
break;
}
case 8:{
cout<<"请输入道路的起点编号、终点编号、权重和类型(0步行,1车行)：";
int from,to,weight,type;cin>>from>>to>>weight>>type;
Graph& target=(type==0)?gWalk:gCar;
if(addRoad(target,from,to,weight,type)){
saveAllRoads(gWalk,gCar,"data/road.txt");
cout<<"道路添加成功！"<<endl;
}else{
cout<<"道路添加失败！"<<endl;
}
break;
}
case 9:{
cout<<"请输入要删除道路的起点终点编号及类型(0步行,1车行)：";
int from,to,type;cin>>from>>to>>type;
Graph& target=(type==0)?gWalk:gCar;
if(deleteRoad(target,from,to)){
saveAllRoads(gWalk,gCar,"data/road.txt");
cout<<"道路删除成功！"<<endl;
}else{
cout<<"道路删除失败！"<<endl;
}
break;
}
case 10:{
cout<<"请输入要修改道路的起点终点编号及类型(0步行,1车行)：";
int from,to,type;cin>>from>>to>>type;
Graph& target=(type==0)?gWalk:gCar;
int fi=getIdIndex(target.scenes,from);
int ti=getIdIndex(target.scenes,to);
if(fi==-1||ti==-1){
cout<<"编号不存在！"<<endl;
}else{
cout<<"请输入新的权重：";
int weight;cin>>weight;
target.adj[fi][ti]=weight;
target.adj[ti][fi]=weight;
saveAllRoads(gWalk,gCar,"data/road.txt");
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