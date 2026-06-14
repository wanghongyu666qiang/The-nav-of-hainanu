#include "../Graph.h"
#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;



//1. 从文件读取景点数据
bool loadScenes(Graph& g,const string& filename){
ifstream file(filename);
if(!file.is_open()) return false;
string line;
getline(file,line);//跳过表头
int id;
string name,desc;
while(file>>id>>name>>desc){
Scene s={id,name,desc};
g.scenes.push_back(s);
}
file.close();
//初始化邻接矩阵
int n=(int)g.scenes.size();
g.adj.resize(n,vector<int>(n,INT_MAX));
g.roadType.resize(n,vector<int>(n,-1));
g.trafficLights.resize(n,vector<int>(n,0));
for(int i=0;i<n;++i){
g.adj[i][i]=0;//自己到自己的距离为0
}
return true;
}



//2. 从文件读取道路数据(roadType:-1=全部,0=步行,1=车行)
bool loadRoads(Graph& g,const string& filename,int roadType){
ifstream file(filename);
if(!file.is_open()) return false;
string line;
getline(file,line);//跳过表头
int from,to,weight,type,lights=0;
while(getline(file,line)){
if(line.empty()) continue;
istringstream iss(line);
lights=0;
if(!(iss>>from>>to>>weight>>type)) continue;
iss>>lights;//读取红绿灯数量（可选列）
if(roadType!=-1&&type!=roadType)continue;
int fi=getIdIndex(g.scenes,from);
int ti=getIdIndex(g.scenes,to);
if(fi==-1||ti==-1)continue;
//双向赋值到邻接矩阵
g.adj[fi][ti]=weight;
g.roadType[fi][ti]=type;
g.trafficLights[fi][ti]=lights;
g.adj[ti][fi]=weight;
g.roadType[ti][fi]=type;
g.trafficLights[ti][fi]=lights;
}
file.close();
return true;
}


//3. 保存景点
bool saveScenes(const Graph& g,const string& filename){
ofstream file(filename);
if(!file.is_open()) return false;

file<<"编号\t名字\t描述\n";
for(int i=0;i<(int)g.scenes.size();++i){
file<<g.scenes[i].id<<"\t"<<g.scenes[i].name<<"\t"<<g.scenes[i].description<<"\n";
}
file.close();
return true;
}


//4. 保存道路
bool saveRoads(const Graph& g,const string& filename){
ofstream file(filename);
if(!file.is_open()) return false;

file<<"起点\t终点\t距离\t类型\t红绿灯\n";
int n=(int)g.scenes.size();
for(int i=0;i<n;++i){
for(int j=i+1;j<n;++j){
if(g.adj[i][j]!=INT_MAX){
file<<g.scenes[i].id<<"\t"<<g.scenes[j].id<<"\t"
<<g.adj[i][j]<<"\t"<<g.roadType[i][j]<<"\t"<<g.trafficLights[i][j]<<"\n";
}
}
}
file.close();
return true;
}


//5. 合并保存步行图和车行图的道路
bool saveAllRoads(const Graph& walk,const Graph& car,const string& filename){
ofstream file(filename);
if(!file.is_open()) return false;
file<<"起点\t终点\t距离\t类型\n";
int n=(int)walk.scenes.size();
for(int i=0;i<n;++i){
for(int j=i+1;j<n;++j){
if(walk.adj[i][j]!=INT_MAX){
file<<walk.scenes[i].id<<"\t"<<walk.scenes[j].id<<"\t"
<<walk.adj[i][j]<<"\t0\n";
}
if(car.adj[i][j]!=INT_MAX){
file<<car.scenes[i].id<<"\t"<<car.scenes[j].id<<"\t"
<<car.adj[i][j]<<"\t1\n";
}
}
}
file.close();
return true;
}
