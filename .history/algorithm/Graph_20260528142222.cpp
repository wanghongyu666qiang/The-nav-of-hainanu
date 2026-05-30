#include "Graph.h"
#include <queue>
#include <iostream>
#include <algorithm> // 婵烇絽娴傞崰鏍闯閵娧呭晩闁衡偓閸愭彃绀嬮柣銏犵箰缁辩偤鎯冮崟顐㈡嵍 reverse

using namespace std;

vector<int> getShortestPath(const Graph& g, int start, int end, int userType) {//闂佸搫绮岄幏銈呪攦閹邦剦鐓戦柛婵嗗濞撴儼顦查梺鍝勫暙濞撳爼鏌ㄩ悤顖涘闯闁归鍘奸埢鏃堝醇閵夈儙宥夋煛婢舵劧姹為柡鍡欏枎楠炴鈧稒顨婇埞鏍煛娴ｅ吋鐒鹃柨鐔虹帛濡层儲鎷呴敓?
    vector<int> result;
    vector<int> path(g.scenes.size()); // 闂佺娉涢幏鍛矙閸曨厽浜ら柛鏇ㄤ簻瀵潡鏌ㄩ悢娲绘晭濠电姴鍟闁跨噦鎷?vector 闂佸搫鍟惃楣冨锤閹版澘鏋佺€广儱娲ㄥ▓銊╂煛瀹ュ繗绀嬬憸鎵虫櫆绾板﹪寮甸鍕獥婵炲樊鍨伴幏鐑芥晸娴犲瑙﹂柛鏇ㄤ簼閹崇偛鈻庢惔銏℃櫆閻犙嶆嫹
    vector<int> dist(g.scenes.size()); // 闂佺娉涢幏鍛矙閸曨厽浜ら柛鏇ㄤ簻瀵潡鏌ㄩ悤顖涘闯闁?
    vector<int> visited(g.scenes.size()); // 闂佺娉涢幏鍛矙閸曨厽浜ら柛鏇ㄤ簻瀵潡鏌ㄩ悤顖涘闯闁归鍘界紞鍡欌偓娑櫭崕?0 闂佸憡鍨肩€氶潧鈹戦埥鍛秶闁瑰嚖鎷?闂佸憡鍨肩€氶潧鈹戦埥鍛秶闁瑰嚖鎷?
   for(int i=0;i<g.scenes.size();i++){
    dist[i]=g.scenes[start].edges[i].weight; 
    visited[i]=0; 
    if(dist[i]==INT_MAX) path[i]=-1;
    else path[i]=start; 
   }
   visited[start]=1;
   path[start]=-1;//闂佸搫瀚烽崹鎶藉极閹剧粯鐎柛娆忓帠娴艰泛鈽夐幘鐐藉剳闁跨噦鎷?
   for(int i=0;i<g.scenes.size()-1;i++)
   {
    //闂佸憡鐟崹鍦矚閹惧鈻旈柨鐕傛嫹
    int mini=INT_MAX;
    int u = -1;
    for(int j=0;j<g.scenes.size();j++)
    {
if(visited[j]==0&&dist[j]<mini)
{
    mini=dist[j];
    u=j;//u闂佸憡鍨肩€氶潧鈹戦埥鍛秶闁瑰嚖鎷?
}
    }//闂佸憡鐟崹鍦矚閹惧鈻旈柨鐕傛嫹

   if (u == -1) break;
   visited[u]=1;

   //闂佸憡鐟崹鍦矚閹惧鈻旈柨鐕傛嫹
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
   }//闂佸憡鐟崹鍦矚閹惧鈻旈柨鐕傛嫹
}

//娴犲穲nd瀵偓婵娲栧┃顖濈熅瀵?
int current=end;//閻劍娼甸崒銊ョ摠瑜版挸澧犻崶鐐村嚱閸掓壆娈戦懞鍌滃仯
while(current!=-1)
{
result.push_back(current);
current=path[current];//閸ョ偞鍑介崚棰佺瑐娑撯偓娑擃亣濡悙?
}
 std::reverse(result.begin(),result.end());
 return result;
}

vector<int> getTSPRoute(const Graph& g, int start, vector<int> targets, int userType) {
    vector<int> route;
    // ... TSP 缁犳纭?
    return route;
}
