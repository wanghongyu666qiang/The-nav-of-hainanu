#include "../Graph.h"
#include<algorithm>

using namespace std;

bool addScene(Graph& g,int id,string name,string desc){
for(int i=0;i<g.scenes.size();i++)
if(g.scenes[i].id==id) return false;

//如果是邻接矩阵，加入新景点时，要对所有的景点扩展一个维度，本景点也要创建一个那么大的维度
int n=g.scenes.size();

//所有之前的景点增加一个去往新节点的路（初始为不可达）
for(int i=0;i<n;++i){
g.scenes[i].edges.push_back({id,INT_MAX,-1});
}

//新景点初始化
vector<Edge>newEdges(n+1);
for(int j=0;j<n;++j){
newEdges[j]={g.scenes[j].id,INT_MAX,-1};
}
//自己到自己距离为 0
newEdges[n]={id,0,-1};

g.scenes.push_back({id,name,desc,newEdges});
return saveScenes(g,"data/scene.txt");
}
