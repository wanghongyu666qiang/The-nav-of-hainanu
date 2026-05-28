#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <map>

// 1. 景点实体
struct Scene {
    int id;
    std::string name;
    int x;
    int y;
    std::string description;
};

// 2. 道路(边)实体
struct Edge {
    int to;
    int weight;
    int roadType; // 0:混行, 1:人行, 2:机动车
};

// 3. 图控制类
class CampusGraph {
private:
    std::map<int, Scene> scenes;
    std::map<int, std::vector<Edge>> adjList;

public:
    // ======= 基础数据与初始化 =======
    bool loadScenes(const std::string& filename);
    bool loadRoads(const std::string& filename);
    void printGraph();
    std::string getSceneName(int id); 

    // ======= CURD 增删改查模块 =======
    // 景点操作
    bool addScene(int id, const std::string& name, int x, int y, const std::string& desc);
    bool deleteScene(int id);
    bool updateScene(int id, const std::string& newName, int newX, int newY, const std::string& newDesc);

    // 道路操作
    // 注意: 添加/更新边时需要同时更新起点和终点的邻接表 (无向图)
    bool addRoad(int from, int to, int weight, int type);
    bool deleteRoad(int from, int to);
    bool updateRoad(int from, int to, int newWeight, int newType);

    // 数据持久化 (存回磁盘)
    bool saveScenesToFile(const std::string& filename);
    bool saveRoadsToFile(const std::string& filename);

    // ======= 核心算法模块 =======
    // 最短路径 Dijkstra
    std::vector<int> getShortestPath(int start, int end, int userType);

    // 多地点 TSP 最优路径
    std::vector<int> getTSPRoute(int start, std::vector<int> targets, int userType);
};

#endif