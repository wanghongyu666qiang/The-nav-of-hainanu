#include "../Graph.h"
#include<iostream>
#include<fstream>

using namespace std;

bool loadScenes(Graph& g,const string& filename){
ifstream file(filename);
if(!file.is_open()) return false;

string line;
getline(file,line);

int id;
string name,desc;
while(file>>id>>name>>desc){
Scene s={id,name,desc};
g.scenes.push_back(s);
}
file.close();

int n=(int)g.scenes.size();
g.adj.resize(n,vector<int>(n,INT_MAX));
g.roadType.resize(n,vector<int>(n,-1));
for(int i=0;i<n;++i){
g.adj[i][i]=0;
}
return true;
}

bool loadRoads(Graph& g,const string& filename,int roadType){
ifstream file(filename);
if(!file.is_open()) return false;

string line;
getline(file,line);

int from,to,weight,type;
while(file>>from>>to>>weight>>type){
if(roadType!=-1&&type!=roadType)continue;

int fi=getIdIndex(g.scenes,from);
int ti=getIdIndex(g.scenes,to);
if(fi==-1||ti==-1)continue;

g.adj[fi][ti]=weight;
g.roadType[fi][ti]=type;
g.adj[ti][fi]=weight;
g.roadType[ti][fi]=type;
}
file.close();
return true;
}

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

bool saveRoads(const Graph& g,const string& filename){
ofstream file(filename);
if(!file.is_open()) return false;

file<<"起点\t终点\t距离\t类型\n";
int n=(int)g.scenes.size();
for(int i=0;i<n;++i){
for(int j=i+1;j<n;++j){
if(g.adj[i][j]!=INT_MAX){
file<<g.scenes[i].id<<"\t"<<g.scenes[j].id<<"\t"
<<g.adj[i][j]<<"\t"<<g.roadType[i][j]<<"\n";
}
}
}
file.close();
return true;
}

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
