#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
//杩欓噷锛屾垜浠笉浣跨敤#include <iostream>锛屼繚鎸佸ご鏂囦欢鐨勭函鍑€鍜岄珮鏁堛€?

// 1. 杈圭粨鏋勪綋锛屽叾瀹炲氨鏄竴涓妭鐐圭殑閭诲眳锛屽寘鍚潈閲嶅拰閬撹矾绫诲瀷
struct Edge {
    int to;
    int weight;
    int roadType; 
};

// 2. 鏅偣缁撴瀯浣?
struct Scene {
    int id;
    std::string name;
    std::string description;
    std::vector<Edge> edges; // 鉁?璇ユ櫙鐐瑰嚭鍙戠殑鎵€鏈夎竟锛岀洿鎺ヤ繚瀛樺湪瀹冭嚜宸辫韩涓婏紒
};

// 3. 鎶婃墍鏈夌殑鍥炬暟鎹墦鍖呰繘涓€涓ぇ缁撴瀯浣撻噷锛屾柟渚夸紶鏉ヤ紶鍘伙紝鏁版嵁鐨勫ぇ蹇冭剰
struct Graph {
    std::vector<Scene> scenes; // 鉁?涓嶅啀浣跨敤map锛屾墍鏈夋櫙鐐规寜椤哄簭瀛樺湪鍔ㄦ€佹暟缁勯噷
};

// 鍚庡嫟鍑芥暟锛堝寘鎷鍒犳敼鏌ワ級 (鍦?curd.cpp 閲?
// 浼犲叆 Graph& g 浠ｈ〃鎴戜滑瑕佷慨鏀硅繖骞呭浘
bool loadScenes(Graph& g, const std::string& filename);
bool loadRoads(Graph& g, const std::string& filename);
bool saveScenes(const Graph& g, const std::string& filename);
bool saveRoads(const Graph& g, const std::string& filename);
bool addScene(Graph& g, int id, std::string name, std::string desc);
bool deleteScene(Graph& g, int id);
bool updateScene(Graph& g, int id, std::string name, std::string desc);
bool addRoad(Graph& g, int from, int to, int weight, int type);
bool deleteRoad(Graph& g, int from, int to);
bool updateRoad(Graph& g, int from, int to, int weight, int type);

// 绠楁硶鍑芥暟 (algorithm.cpp 閲?
// 浼犲叆 const Graph& g 浠ｈ〃绠楁硶鍙鍙栧浘锛屼笉淇敼鍥?
std::vector<int> getShortestPath(const Graph& g, int start, int end, int userType);
std::vector<int> getTSPRoute(const Graph& g, int start, std::vector<int> targets, int userType);

#endif