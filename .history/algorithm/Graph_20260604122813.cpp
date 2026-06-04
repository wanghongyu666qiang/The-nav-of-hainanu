#include "Graph.h"
#include<iostream>
#include<algorithm>//reverse
#include<unordered_map>
using namespace std;

void getshortestpath(const Graph& g,int start,int end,int userType){//采用dijistra算法
vector<int>result;
vector<int>path(g.scenes.size());//存储路径
vector<int>dist(g.scenes.size());//存储距离
vector<int>visited(g.scenes.size());//存储访问状态,0表示未访问，1表示已访问
//全部用动态数组，防止环境报错
for(int i=0;i<g.scenes.size();i++){
dist[i]=g.adj[start][i];
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
for(int v=0;v<g.scenes.size();v++)
{
if(visited[v]==0)
{
if(dist[u]!=INT_MAX&&g.adj[u][v]!=INT_MAX&&dist[u]+g.adj[u][v]<dist[v])//健壮性加强，两个大的无穷大相加可能会溢出变成负数，所以要先判断dist[u]和g.adj[u][v]是否为INT_MAX
{
dist[v]=dist[u]+g.adj[u][v];
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
void dfsAllPaths(const Graph& g,int cur,int end,vector<int>& visited,vector<int>& path,int& cnt,int what,unordered_map<int,int>& requiredPlaces){//为了后面的方便，我把这个函数的参数设计得比较多，what用来区分是普通枚举路径还是满足条件的路径，requiredPlaces是满足条件的路径需要经过的地点的哈希表
visited[cur]=1;
path.push_back(cur);
if(cur==end){

if(what==0)
{
    cnt++;
cout<<"路径"<<cnt<<": ";
int total=0;
for(int i=0;i<path.size();i++){
cout<<g.scenes[path[i]].name;
if(i<path.size()-1){
total+=g.adj[path[i]][path[i+1]];
cout<<" -> ";
}
}
cout<<"(距离:"<<total<<")"<<endl;
}
//这段是用于whatyouwant函数的
else//else if(what==1)
{   unordered_map<int,int> temp=requiredPlaces;//先把哈希表复制一份，后面要修改这个哈希表，所以不能直接修改原来的哈希表，不然会影响后续的路径判断
    for(int i=0;i<path.size();i++)
    {   if(temp.find(g.scenes[path[i]].id)!=temp.end())//如果这个地点在哈希表里，才能减，我这不是数组做的哈希表，所以直接find就行了，不需要判断索引
        temp[g.scenes[path[i]].id]--;//把路径上经过的地点在哈希表里对应的数量--，如果最后哈希表里所有值都小于1，就说明满足条件了
    }
    bool allLessThanOne=true;
    for(auto it:temp)//遍历哈希表，判断是否所有值都小于1
    {
        if(it.second>=1)
        {
            allLessThanOne=false;
            break;
        }
    }
    if(allLessThanOne)//if
    {   cnt++;
        cout<<"满足条件的路径"<<cnt<<": ";
        int total=0;
        for(int i=0;i<path.size();i++){
        cout<<g.scenes[path[i]].name;
        if(i<path.size()-1){
        total+=g.adj[path[i]][path[i+1]];
        cout<<" -> ";
        }
        }
        cout<<"(距离:"<<total<<")"<<endl;
    }//if
}//else

} 
else {
for(int v=0;v<g.scenes.size();v++){
if(!visited[v]&&g.adj[cur][v]!=INT_MAX)
dfsAllPaths(g,v,end,visited,path,cnt,what,requiredPlaces);
}
}
path.pop_back();
visited[cur]=0;
}

void findAllPaths(const Graph& g,int start,int end){
vector<int>visited(g.scenes.size(),0);
vector<int>path;
int cnt=0;
int what=0;//0表示普通枚举路径，1表示满足条件的路径
unordered_map<int,int> requiredPlaces;//这个函数里不需要这个哈希表，所以传一个空的就行了
dfsAllPaths(g,start,end,visited,path,cnt,what,requiredPlaces);
if(cnt==0) cout<<"未找到任何路径！"<<endl;
}


void whatyouwant(const Graph& g)
{
    cout<<"请输入起点和终点的编号：";
    int start,end;
    cin>>start>>end;
    int startIndex=-1,endIndex=-1;
    for(int i=0;i<g.scenes.size();i++){
        if(g.scenes[i].id==start) startIndex=i;
        if(g.scenes[i].id==end) endIndex=i;
    }//还是要先找到对应的索引，我输入的是编号，不是它在vector中的位置
    if(startIndex==-1||endIndex==-1){
        cout<<"输入的编号无效！"<<endl;
        return;
    }
    cout<<"请输入必经地点的数量和编号：";
    int n;
    cin>>n;
    unordered_map<int,int> requiredPlaces;//用哈希表来存，到时候直接--,如果小于1，就代表经过了，要全部小于1才算满足条件
    for(int i=0;i<n;i++){
        int placeId;
        cin>>placeId;
        requiredPlaces[placeId]++;
    }
//这里我用dfs来枚举所有路径，再来减--哈希表里对应的地点数量，最后判断哈希表里所有值是否都小于1，如果是，就输出这条路径
vector<int>visited(g.scenes.size(),0);
vector<int>path;
int cnt=0;
int what=1;//1表示满足条件的路径
dfsAllPaths(g,startIndex,endIndex,visited,path,cnt,what,requiredPlaces);
if(cnt==0) cout<<"未找到满足条件的路径！"<<endl;
}