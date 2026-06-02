#include "../Graph.h"
#include<algorithm>

using namespace std;

bool addScene(Graph& g,int id,string name,string desc){
for(int i=0;i<(int)g.scenes.size();i++)
if(g.scenes[i].id==id) return false;

int n=(int)g.scenes.size();
g.adj.resize(n+1);
g.roadType.resize(n+1);
for(int i=0;i<=n;++i){
g.adj[i].resize(n+1,INT_MAX);
g.roadType[i].resize(n+1,-1);
}
g.adj[n][n]=0;

g.scenes.push_back({id,name,desc});
return true;
}
