#include "Graph.h"
#include <queue>
#include <iostream>

using namespace std;



vector<int> getShortestPath(const Graph& g, int start, int end, int userType) {//采用dijistra算法
    vector<int> path;
    int pathArr[g.scenes.size()]; // 存储路径
    int dist[g.scenes.size()]; // 存储距离
    int visited[g.scenes.size()]; // 存储访问状态,0表示未访问，1表示已访问
   const vector<Edge>& startEdges = (userType == 0) ? g.scenes[start].walkEdges : g.scenes[start].driveEdges;
   for(int i=0;i<g.scenes.size();i++){
    dist[i]=INT_MAX; 
    visited[i]=0; 
    pathArr[i]=-1;
   }
   for (const Edge& e : startEdges) {
       dist[e.to] = e.weight;
       pathArr[e.to] = start;
   }
   dist[start]=0;
   visited[start]=1;
   pathArr[start]=-1;//完成初始化
   for(int i=0;i<g.scenes.size()-1;i++)
   {
    //找到没被访问的节点距离源点最近的节点
    int mini=INT_MAX;
    int u;
    for(int j=0;j<g.scenes.size();j++)
    {
if(visited[j]==0&&dist[j]<mini)
{
    mini=dist[j];
    u=j;//u就是当前距离源点最近的节点
}
    }//找最近的节点的for
   visited[u]=1;

   //更新u的邻居节点的距离的for
   for(int v=0;v<g.scenes[u].edges.size();v++)
   {
if(visited[v]==0)
{
    if(dist[u]+g.scenes[u].edges[v].weight<dist[v])
    {
        dist[v]=dist[u]+g.scenes[u].edges[v].weight;
        path[v]=u;
    }
}
   }//更新u的邻居节点的距离for
}


}

vector<int> getTSPRoute(const Graph& g, int start, vector<int> targets, int userType) {
    vector<int> route;
    // ... TSP 算法
    return route;
}