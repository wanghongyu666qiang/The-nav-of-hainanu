#include "../Graph.h"

using namespace std;

bool addRoad(Graph& g,int from,int to,int weight,int type,int lights){
int fi=getIdIndex(g.scenes,from);
int ti=getIdIndex(g.scenes,to);
if(fi==-1||ti==-1) return false;

g.adj[fi][ti]=weight;
g.roadType[fi][ti]=type;
g.trafficLights[fi][ti]=lights;
g.adj[ti][fi]=weight;
g.roadType[ti][fi]=type;
g.trafficLights[ti][fi]=lights;
return true;
}
