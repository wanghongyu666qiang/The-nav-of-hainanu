#include "Graph.h"
#include <queue>
#include <iostream>

using namespace std;



vector<int> getShortestPath(const Graph& g, int start, int end, int userType) {//閲囩敤dijistra绠楁硶
    vector<int> path;
    int pathArr[g.scenes.size()]; // 瀛樺偍璺緞
    int dist[g.scenes.size()]; // 瀛樺偍璺濈
    int visited[g.scenes.size()]; // 瀛樺偍璁块棶鐘舵€?0琛ㄧず鏈闂紝1琛ㄧず宸茶闂?
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
   pathArr[start]=-1;//瀹屾垚鍒濆鍖?
   for(int i=0;i<g.scenes.size()-1;i++)
   {
    //鎵惧埌娌¤璁块棶鐨勮妭鐐硅窛绂绘簮鐐规渶杩戠殑鑺傜偣
    int mini=INT_MAX;
    int u;
    for(int j=0;j<g.scenes.size();j++)
    {
if(visited[j]==0&&dist[j]<mini)
{
    mini=dist[j];
    u=j;//u灏辨槸褰撳墠璺濈婧愮偣鏈€杩戠殑鑺傜偣
}
    }//鎵炬渶杩戠殑鑺傜偣鐨刦or
   visited[u]=1;

   //鏇存柊u鐨勯偦灞呰妭鐐圭殑璺濈鐨刦or
   const vector<Edge>& uEdges = (userType == 0) ? g.scenes[u].walkEdges : g.scenes[u].driveEdges;
   for(int v=0;v<uEdges.size();v++)
   {
    int neighbor = uEdges[v].to;
if(visited[neighbor]==0)
{
    if(dist[u]+uEdges[v].weight<dist[neighbor])
    {
        dist[neighbor]=dist[u]+uEdges[v].weight;
        pathArr[neighbor]=u;
    }
}
   }//鏇存柊u鐨勯偦灞呰妭鐐圭殑璺濈for
}


}

vector<int> getTSPRoute(const Graph& g, int start, vector<int> targets, int userType) {
    vector<int> route;
    // ... TSP 绠楁硶
    return route;
}