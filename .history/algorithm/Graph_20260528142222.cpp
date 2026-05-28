#include "Graph.h"
#include <queue>
#include <iostream>
#include <algorithm> // 濞ｅ浂鍠栭崳銊х啊閺€鍐插礋閻㈠繐绱為惃鍕捶 reverse

using namespace std;

vector<int> getShortestPath(const Graph& g, int start, int end, int userType) {//闁哄粌鎷ゅ┃鎰煑閸濆嫬娓惰闁哄啫娓堕柨鐕崳閹额厼鈻旈崼銉ノ嶉柡澶愶汞閺嗙喎骞樼€涙鈹栭柡浣兼焾閿熺粯妲ユ担锟?
    vector<int> result;
    vector<int> path(g.scenes.size()); // 闁硅泛鎷呯粙鍕交閸曨亜寮块柨鐔活敎婵犲啫袝閿燂拷 vector 闁哄啫鐨鹃崸鎰板极瀹ュ洨娈ㄩ柡宥忚礋瑜扳晜纰婇張顏勭窗濞差垰鎷烽敓浠嬪触閸曨亝鎳炲▎搴㈡晜鐠э拷
    vector<int> dist(g.scenes.size()); // 闁硅泛鎷呯粙鍕交閸曨亜寮块柨鐕崳閹?
    vector<int> visited(g.scenes.size()); // 闁硅泛鎷呯粙鍕交閸曨亜寮块柨鐕崳閹额厽缍嗙€涙ê鍎?0 闁告垼瀚靛┑鈽呮綇閹凤拷1闁告垼瀚靛┑鈽呮綇閹凤拷
   for(int i=0;i<g.scenes.size();i++){
    dist[i]=g.scenes[start].edges[i].weight; 
    visited[i]=0; 
    if(dist[i]==INT_MAX) path[i]=-1;
    else path[i]=start; 
   }
   visited[start]=1;
   path[start]=-1;//闁哄嫷鍨抽弫鎾绘瀮閸欏厖浼跺☉鎾炽儑閿燂拷
   for(int i=0;i<g.scenes.size()-1;i++)
   {
    //闁告瑯鍨圭粚鎾寸▔閿燂拷
    int mini=INT_MAX;
    int u = -1;
    for(int j=0;j<g.scenes.size();j++)
    {
if(visited[j]==0&&dist[j]<mini)
{
    mini=dist[j];
    u=j;//u闁告垼瀚靛┑鈽呮綇閹凤拷
}
    }//闁告瑯鍨圭粚鎾寸▔閿燂拷

   if (u == -1) break;
   visited[u]=1;

   //闁告瑯鍨圭粚鎾寸▔閿燂拷
   for(int v=0;v<g.scenes[u].edges.size();v++)
   {
if(visited[v]==0)
{
    if(dist[u] != INT_MAX && g.scenes[u].edges[v].weight != INT_MAX)
    {
       if(dist[u]+g.scenes[u].edges[v].weight<dist[v])
       {
           dist[v]=dist[u]+g.scenes[u].edges[v].weight;
           path[v]=u;
       }
    }
}
   }//闁告瑯鍨圭粚鎾寸▔閿燂拷
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
