#include "Graph.h"
#include<iostream>
#include<algorithm>//reverse
using namespace std;

void getshortestpath(const Graph& g,int start,int end,int userType){//采用dijistra算法
vector<int>result;
vector<int>path(g.scenes.size());//存储路径
vector<int>dist(g.scenes.size());//存储距离
vector<int>visited(g.scenes.size());//存储访问状态,0表示未访问，1表示已访问
//全部用动态数组，防止环境报错
for(int i=0;i<g.scenes.size();i++){
dist[i]=g.scenes[start].edges[i].weight;
visited[i]=0;
if(dist[i]==INT_MAX) path[i]=-1;
else path[i]=start;
}
visited[start]=1;
path[start]=-1;//完成初始化
for(int i=0;i<g.scenes.size()-1;i++)
{
//找到没被访问的节点距离源点最近的节点
int mini=INT_MAX;
int u=-1;
for(int j=0;j<g.scenes.size();j++)
{
if(visited[j]==0&&dist[j]<mini)
{
mini=dist[j];
u=j;//u就是当前距离源点最近的节点
}
}//找最近的节点的for
if(u==-1) break;
else
visited[u]=1;

//更新u的邻居节点的距离的for
for(int v=0;v<g.scenes[u].edges.size();v++)
{
if(visited[v]==0)
{
if(dist[u]!=INT_MAX&&g.scenes[u].edges[v].weight!=INT_MAX&&dist[u]+g.scenes[u].edges[v].weight<dist[v])//健壮性加强，两个大的无穷大相加可能会溢出变成负数，所以要先判断dist[u]和g.scenes[u].edges[v].weight是否为INT_MAX
{
dist[v]=dist[u]+g.scenes[u].edges[v].weight;
path[v]=u;
}
}
}//更新u的邻居节点的距离for
}

//从end开始回溯路径
int current=end;//用来储存当前回溯到的节点
while(current!=-1)
{
result.push_back(current);
current=path[current];//回溯到上一个节点
}
std::reverse(result.begin(),result.end());

if(dist[end]==INT_MAX){
cout<<"无可达路径！"<<endl;
} else {
cout<<"最短路径长度为："<<dist[end]<<endl;
cout<<"路径为：";
for(int i=0;i<result.size();i++){
cout<<g.scenes[result[i]].name<<" ";
}
cout<<endl;
}

}

//DFS 枚举两景点间所有路径
void dfsAllPaths(const Graph& g,int cur,int end,
vector<int>& visited,vector<int>& path,int& cnt){
visited[cur]=1;
path.push_back(cur);
if(cur==end){
cnt++;
cout<<"路径"<<cnt<<": ";
int total=0;
for(int i=0;i<path.size();i++){
cout<<g.scenes[path[i]].name;
if(i<path.size()-1){
total+=g.scenes[path[i]].edges[path[i+1]].weight;
cout<<" -> ";
}
}
cout<<"   (距离: "<<total<<")"<<endl;
} else {
for(int v=0;v<g.scenes.size();v++){
if(!visited[v]&&g.scenes[cur].edges[v].weight!=INT_MAX)
dfsAllPaths(g,v,end,visited,path,cnt);
}
}
path.pop_back();
visited[cur]=0;
}

void findAllPaths(const Graph& g,int start,int end){
vector<int>visited(g.scenes.size(),0);
vector<int>path;
int cnt=0;
dfsAllPaths(g,start,end,visited,path,cnt);
if(cnt==0) cout<<"未找到任何路径！"<<endl;
}

