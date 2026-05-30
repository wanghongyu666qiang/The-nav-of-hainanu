#include <iostream>
#include "algorithm/Graph.h"

using namespace std;

int main() {
    // 1. 澹版槑涓€涓寘鍚簡鏅偣鍜岃竟鐨勫浘鍙橀噺
    Graph myGraph; 

    // 2. 璋冪敤鍑芥暟鎶婃暟鎹杩涘幓 (鎶?myGraph 浣滀负鍙傛暟浼犺繘鍘诲～婊?
    loadScenes(myGraph, "data/scene.txt");
    loadRoads(myGraph, "data/road.txt");

    // 3. 娴嬭瘯澧炲垹鏀规煡
    addScene(myGraph, 6, "瀹胯垗妤?, "鐫¤鐨勫湴鏂?);
    
    // 4. 娴嬭瘯绠楁硶
    vector<int> path = getShortestPath(myGraph, 1, 4, 1);

    return 0;
}