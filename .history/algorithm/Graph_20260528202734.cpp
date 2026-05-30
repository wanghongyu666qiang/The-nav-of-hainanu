#include "Graph.h"
#include <queue>
#include <iostream>

using namespace std;

vector<int> getShortestPath(const Graph& g, int start, int end, int userType) {//閲囩敤dijistra绠楁硶
    vector<int> result;
    vector<int> path(g.scenes.size()); // 瀛樺偍璺緞
    vector<int> dist(g.scenes.size()); // 瀛樺偍璺濈
    vector<int> visited(g.scenes.size()); // 瀛樺偍璁块棶鐘舵€?0琛ㄧず鏈闂紝1琛ㄧず宸茶闂?
    //鍏ㄩ儴鐢ㄥ姩鎬佹暟缁勶紝闃叉鐜鎶ラ敊
   for(int i=0;i<g.scenes.size();i++){
    dist[i]=g.scenes[start].edges[i].weight; 
    visited[i]=0; 
    if(dist[i]==INT_MAX) path[i]=-1;
    else path[i]=start; 
   }
   visited[start]=1;
   path[start]=-1;//瀹屾垚鍒濆鍖?
   for(int i=0;i<g.scenes.size()-1;i++)
   {
    //鎵惧埌娌¤璁块棶鐨勮妭鐐硅窛绂绘簮鐐规渶杩戠殑鑺傜偣
    int mini=INT_MAX;
    int u=-1;
    for(int j=0;j<g.scenes.size();j++)
    {
if(visited[j]==0&&dist[j]<mini)
{
    mini=dist[j];
    u=j;//u灏辨槸褰撳墠璺濈婧愮偣鏈€杩戠殑鑺傜偣
}
    }//鎵炬渶杩戠殑鑺傜偣鐨刦or
    if(u==-1) break;
    else
     visited[u]=1;

   //鏇存柊u鐨勯偦灞呰妭鐐圭殑璺濈鐨刦or
   for(int v=0;v<g.scenes[u].edges.size();v++)
   {
if(visited[v]==0)
{
    if(dist[u]!=INT_MAX && g.scenes[u].edges[v].weight!=INT_MAX && dist[u]+g.scenes[u].edges[v].weight<dist[v])//鍋ュ．鎬у姞寮猴紝涓や釜澶х殑鏃犵┓澶х浉鍔犲彲鑳戒細婧㈠嚭鍙樻垚璐熸暟锛屾墍浠ヨ鍏堝垽鏂璬ist[u]鍜実.scenes[u].edges[v].weight鏄惁涓篒NT_MAX
    {
        dist[v]=dist[u]+g.scenes[u].edges[v].weight;
        path[v]=u;
    }
}
   }//鏇存柊u鐨勯偦灞呰妭鐐圭殑璺濈for
}

//浠巈nd寮€濮嬪洖婧矾寰?
int current=end;//鐢ㄦ潵鍌ㄥ瓨褰撳墠鍥炴函鍒扮殑鑺傜偣
while(current!=-1)
{
result.push_back(current);
current=path[current];//鍥炴函鍒颁笂涓€涓妭鐐?
}
 std::reverse(result.begin(),result.end());
 return result;
}

vector<int> getTSPRoute(const Graph& g, int start, vector<int> targets, int userType) {
    vector<int> route;
    // ... TSP 绠楁硶
    return route;
}