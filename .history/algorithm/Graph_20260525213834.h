#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <map>

// 1. 鏅偣缁撴瀯浣?(鏍规嵁浣犳渶鏂扮殑txt锛屽幓鎺変簡X鍜孻)
struct Scene {
    int id;
    std::string name;
    std::string description;
};

// 2. 杈圭粨鏋勪綋
struct Edge {
    int to;
    int weight;
    int roadType; 
};

// 3. 鎶婃墍鏈夌殑鍥炬暟鎹墦鍖呰繘涓€涓ぇ缁撴瀯浣撻噷锛屾柟渚夸紶鏉ヤ紶鍘伙紝鏁版嵁鐨勫ぇ蹇冭剰
struct Graph {
    std::map<int, Scene> scenes;// 鐢?id 浣滀负 key锛孲cene 浣滀负 value锛岀敤鏉ユ煡鎵炬櫙鐐逛俊鎭紝鏂逛究灏嗘暟瀛楀拰鏂囧瓧杞寲
    std::map<int, std::vector<Edge>> adjList;//閭绘帴琛紝鐢ㄦ潵瀛樺偍鍥剧殑缁撴瀯鍜屾潈閲?
};

// ====== 鎵€鏈夌殑鍏ㄥ眬鍑芥暟澹版槑 (鍚戝瀵煎嚭) ======

// 鍚庡嫟鍑芥暟 (浠ュ墠鍦?curd.cpp 閲?
// 浼犲叆 Graph& g 浠ｈ〃鎴戜滑瑕佷慨鏀硅繖骞呭浘
bool loadScenes(Graph& g, const std::string& filename);
bool loadRoads(Graph& g, const std::string& filename);
bool saveScenes(const Graph& g, const std::string& filename);
bool addScene(Graph& g, int id, std::string name, std::string desc);
bool deleteScene(Graph& g, int id);
bool addRoad(Graph& g, int from, int to, int weight, int type);

// 绠楁硶鍑芥暟 (浠ュ墠鍦?algorithm.cpp 閲?
// 浼犲叆 const Graph& g 浠ｈ〃绠楁硶鍙鍙栧浘锛屼笉淇敼鍥?
std::vector<int> getShortestPath(const Graph& g, int start, int end, int userType);
std::vector<int> getTSPRoute(const Graph& g, int start, std::vector<int> targets, int userType);

#endif