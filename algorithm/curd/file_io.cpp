#include "../Graph.h"
#include<iostream>
#include<fstream>

using namespace std;

//1. 从文件读取景点数据
bool loadScenes(Graph& g,const string& filename){
ifstream file(filename);
if(!file.is_open()) return false;

string line;
//先读一行废弃掉（因为第一行是中文表头："编号  名字  描述"）
getline(file,line);

int id;
string name,desc;
while(file>>id>>name>>desc){
//先建立空的 edges
Scene s={id,name,desc,vector<Edge>()};
g.scenes.push_back(s);
}
file.close();

//在读取完所有景点后，初始化每个景点的邻接矩阵数据结构
int n=g.scenes.size();
for(int i=0;i<n;++i){
g.scenes[i].edges.resize(n);//大小与景点数量相同
for(int j=0;j<n;++j){
//用每个位置对应的景点 ID 填充 to 字段，权重初始化为 INT_MAX
g.scenes[i].edges[j]={g.scenes[j].id,INT_MAX,-1};
}
//自己到自己的距离为 0
g.scenes[i].edges[i].weight=0;
}
return true;
}

//2. 从文件读取道路数据(roadType:-1=全部,0=步行,1=车行)
bool loadRoads(Graph& g,const string& filename,int roadType){
ifstream file(filename);
if(!file.is_open()) return false;

string line;
//先读一行废弃掉表头（"起点  终点  距离  类型"）
getline(file,line);

int from,to,weight,type;
while(file>>from>>to>>weight>>type){
//过滤:只加载指定类型的道路(roadType=-1则全加载)
if(roadType!=-1&&type!=roadType)continue;
//因为是邻接矩阵，我们需要通过 ID 找到对应的索引
int fromIndex=-1;for(int i=0;i<g.scenes.size();i++) if(g.scenes[i].id==from){fromIndex=i;break;};
int toIndex=-1;for(int i=0;i<g.scenes.size();i++) if(g.scenes[i].id==to){toIndex=i;break;};

//双向赋值（覆盖原本的 INT_MAX）
if(fromIndex!=-1&&toIndex!=-1){
g.scenes[fromIndex].edges[toIndex].weight=weight;
g.scenes[fromIndex].edges[toIndex].roadType=type;

g.scenes[toIndex].edges[fromIndex].weight=weight;
g.scenes[toIndex].edges[fromIndex].roadType=type;
}
}
file.close();
return true;
}

//3. 将内存里的景点数据写回文件（持久化）
bool saveScenes(const Graph& g,const string& filename){
ofstream file(filename);
if(!file.is_open()) return false;

file<<"编号\t名字\t描述\n";//写入表头
for(const Scene& s :g.scenes){
file<<s.id<<"\t"<<s.name<<"\t"<<s.description<<"\n";
}
file.close();
return true;
}

//4. 将内存里的道路数据写回文件（持久化）
bool saveRoads(const Graph& g,const string& filename){
ofstream file(filename);
if(!file.is_open()) return false;

file<<"起点\t终点\t距离\t类型\n";//写入表头
for(int i=0;i<g.scenes.size();++i){
for(int j=i+1;j<g.scenes.size();++j){
//只要不是无穷大，且不是自身，说明有一条路
if(g.scenes[i].edges[j].weight!=INT_MAX){
file<<g.scenes[i].id<<"\t"
<<g.scenes[j].id<<"\t"
<<g.scenes[i].edges[j].weight<<"\t"
<<g.scenes[i].edges[j].roadType<<"\n";
}
}
}
file.close();
return true;
}

//提取指定道路类型的邻接矩阵图，供算法使用
Graph getFilteredGraph(const Graph& g,int roadType){
Graph res;
//只拷贝景点元数据，不拷贝 edges（避免无用深拷贝）
for(int i=0;i<g.scenes.size();i++)
res.scenes.push_back({g.scenes[i].id,g.scenes[i].name,g.scenes[i].description,{}});
for(int i=0;i<res.scenes.size();++i){
std::vector<Edge>matrixEdges(res.scenes.size());
for(int j=0;j<res.scenes.size();++j){
matrixEdges[j]={res.scenes[j].id,INT_MAX,roadType};
}
matrixEdges[i].weight=0;
for(int j=0;j<g.scenes[i].edges.size();j++){
if(g.scenes[i].edges[j].roadType==roadType){
int ti=-1;
for(int k=0;k<res.scenes.size();k++)
if(res.scenes[k].id==g.scenes[i].edges[j].to){ti=k;break;}
if(ti!=-1) matrixEdges[ti].weight=g.scenes[i].edges[j].weight;
}
}
res.scenes[i].edges=matrixEdges;
}
return res;
}

//5. 合并保存步行图和车行图的道路到一个文件
bool saveAllRoads(const Graph& walk,const Graph& car,const string& filename){
ofstream file(filename);
if(!file.is_open()) return false;
file<<"起点\t终点\t距离\t类型\n";
int n=(int)walk.scenes.size();
for(int i=0;i<n;++i){
for(int j=i+1;j<n;++j){
//保存步行道
if(walk.scenes[i].edges[j].weight!=INT_MAX){
file<<walk.scenes[i].id<<"\t"<<walk.scenes[j].id<<"\t"
<<walk.scenes[i].edges[j].weight<<"\t0\n";
}
//保存车行道
if(car.scenes[i].edges[j].weight!=INT_MAX){
file<<car.scenes[i].id<<"\t"<<car.scenes[j].id<<"\t"
<<car.scenes[i].edges[j].weight<<"\t1\n";
}
}
}
file.close();
return true;
}
