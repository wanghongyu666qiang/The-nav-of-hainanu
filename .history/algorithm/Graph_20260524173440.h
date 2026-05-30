#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <map>

// 1. 鏅偣瀹炰綋
struct Scene {
    int id;
    std::string name;
    int x;
    int y;
    std::string description;
};

// 2. 閬撹矾(杈?瀹炰綋
struct Edge {
    int to;
    int weight;
    int roadType; // 0:娣疯, 1:浜鸿, 2:鏈哄姩杞?
};

// 3. 鍥炬帶鍒剁被
class CampusGraph {
private:
    std::map<int, Scene> scenes;
    std::map<int, std::vector<Edge>> adjList;

public:
    // ======= 鍩虹鏁版嵁涓庡垵濮嬪寲 =======
    bool loadScenes(const std::string& filename);
    bool loadRoads(const std::string& filename);
    void printGraph();
    std::string getSceneName(int id); 

    // ======= CURD 澧炲垹鏀规煡妯″潡 =======
    // 鏅偣鎿嶄綔
    bool addScene(int id, const std::string& name, int x, int y, const std::string& desc);
    bool deleteScene(int id);
    bool updateScene(int id, const std::string& newName, int newX, int newY, const std::string& newDesc);

    // 閬撹矾鎿嶄綔
    // 娉ㄦ剰: 娣诲姞/鏇存柊杈规椂闇€瑕佸悓鏃舵洿鏂拌捣鐐瑰拰缁堢偣鐨勯偦鎺ヨ〃 (鏃犲悜鍥?
    bool addRoad(int from, int to, int weight, int type);
    bool deleteRoad(int from, int to);
    bool updateRoad(int from, int to, int newWeight, int newType);

    // 鏁版嵁鎸佷箙鍖?(瀛樺洖纾佺洏)
    bool saveScenesToFile(const std::string& filename);
    bool saveRoadsToFile(const std::string& filename);

    // ======= 鏍稿績绠楁硶妯″潡 =======
    // 鏈€鐭矾寰?Dijkstra
    std::vector<int> getShortestPath(int start, int end, int userType);

    // 澶氬湴鐐?TSP 鏈€浼樿矾寰?
    std::vector<int> getTSPRoute(int start, std::vector<int> targets, int userType);
};

#endif