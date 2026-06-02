#include "../Graph.h"
#include<algorithm>

using namespace std;

bool deleteScene(Graph& g,int id){
int index=-1;for(int i=0;i<(int)g.scenes.size();i++) if(g.scenes[i].id==id){index=i;break;}
if(index==-1) return false;

g.scenes.erase(g.scenes.begin()+index);

g.adj.erase(g.adj.begin()+index);
g.roadType.erase(g.roadType.begin()+index);
for(int k=0;k<(int)g.scenes.size();k++){
g.adj[k].erase(g.adj[k].begin()+index);
g.roadType[k].erase(g.roadType[k].begin()+index);
}
return true;
}
