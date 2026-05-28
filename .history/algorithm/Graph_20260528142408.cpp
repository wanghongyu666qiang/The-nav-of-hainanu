#include "Graph.h"
#include <queue>
#include <iostream>

using namespace std;



vector<int> getShortestPath(const Graph& g, int start, int end, int userType) {//采用dijistra算法
    vector<int> result;
    vector<int> path(g.scenes.size()); // 存储路径
    vector<int> dist(g.scenes.size()); // 存储距离
    vector<int> visited(g.scenes.size()); // 存储访问状态,0表示未访问，1表示已访问
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
    if(dist[u]!=INT_MAX && g.scenes[u].edges[v].weight!=INT_MAX && dist[u]+g.scenes[u].edges[v].weight<dist[v])//健壮性加强，两个大的无穷大相加可能会溢出变成负数，所以要先判断dist[u]和g.scenes[u].edges[v].weight是否为INT_MAX
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
 return result;
}

vector<int> getTSPRoute(const Graph& g, int start, vector<int> targets, int userType) {
    vector<int> route;
    // ... TSP 算法
    return route;
}