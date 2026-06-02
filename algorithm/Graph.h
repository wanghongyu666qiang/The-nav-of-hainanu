#ifndef GRAPH_H
#define GRAPH_H

#include<string>
#include<vector>
#include<climits>//INT_MAX

struct Scene {
int id;
std::string name;
std::string description;
};

struct Graph {
std::vector<Scene>scenes;
std::vector<std::vector<int>>adj;
std::vector<std::vector<int>>roadType;
};

inline int getIdIndex(const std::vector<Scene>& scenes,int id){
for(int i=0;i<(int)scenes.size();++i)
if(scenes[i].id==id) return i;
return-1;
}

bool loadScenes(Graph& g,const std::string& filename);
bool loadRoads(Graph& g,const std::string& filename,int roadType=-1);
bool saveScenes(const Graph& g,const std::string& filename);
bool saveRoads(const Graph& g,const std::string& filename);
bool saveAllRoads(const Graph& walk,const Graph& car,const std::string& filename);
bool addScene(Graph& g,int id,std::string name,std::string desc);
bool deleteScene(Graph& g,int id);
bool updateScene(Graph& g,int id,std::string name,std::string desc);
bool addRoad(Graph& g,int from,int to,int weight,int type);
bool deleteRoad(Graph& g,int from,int to);
bool updateRoad(Graph& g,int from,int to,int weight,int type);
void printScenes(const Graph& g);

void getshortestpath(const Graph& g,int start,int end,int userType);
void findAllPaths(const Graph& g,int start,int end);

#endif
