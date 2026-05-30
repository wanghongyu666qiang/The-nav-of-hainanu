#include "../Graph.h"

using namespace std;

bool addRoad(Graph& g,int from,int to,int weight,int type){
int fromIndex=-1;for(int i=0;i<g.scenes.size();i++) if(g.scenes[i].id==from){fromIndex=i;break;};
int toIndex=-1;for(int i=0;i<g.scenes.size();i++) if(g.scenes[i].id==to){toIndex=i;break;};
if(fromIndex==-1||toIndex==-1) return false;

//ÐÞ¸ÄÁÚ½Ó¾ØÕó
g.scenes[fromIndex].edges[toIndex]={to,weight,type};
g.scenes[toIndex].edges[fromIndex]={from,weight,type};
saveRoads(g,"data/road.txt");
return true;
}
