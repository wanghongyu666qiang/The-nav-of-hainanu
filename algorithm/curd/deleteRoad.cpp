#include "../Graph.h"

using namespace std;

bool deleteRoad(Graph& g,int from,int to){
int fi=getIdIndex(g.scenes,from);
int ti=getIdIndex(g.scenes,to);
if(fi==-1||ti==-1) return false;

if(g.adj[fi][ti]!=INT_MAX){
g.adj[fi][ti]=INT_MAX;
g.roadType[fi][ti]=-1;
g.adj[ti][fi]=INT_MAX;
g.roadType[ti][fi]=-1;
return true;
}
return false;
}
