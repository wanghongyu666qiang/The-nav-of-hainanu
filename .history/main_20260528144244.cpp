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
    
    // 4. 灏嗘€昏〃瑙ｈ€︽垚浜鸿閬撳拰杞﹂亾
    Graph walkGraph = getWalkGraph(myGraph);
    Graph driveGraph = getDriveGraph(myGraph);

    // 5. 娴嬭瘯绠楁硶锛堜紶鍏ヨВ鑰﹀ソ鐨勪笓鐢ㄥ浘锛岀‘淇濅互鍘熸湰鐨?Dijkstra 绠楁硶浠ｇ爜涓轰腑蹇冿紝涓嶉渶瑕佷慨鏀瑰畠锛?
    // 鍋囪 userType=0 浠ｈ〃姝ヨ锛寀serType=1 浠ｈ〃杞﹁锛堟渶鍚庨偅涓?0/1 鍙傛暟鍘熸湰娌＄敤鍒帮紝鎵€浠ユ垜浠€氳繃浼犲叆涓嶅悓鐨勪笓鐢ㄥ浘鏉ュ疄鐜拌В鑰︼級
    vector<int> pathWalk = getShortestPath(walkGraph, 1, 4, 0);
    vector<int> pathDrive = getShortestPath(driveGraph, 1, 4, 1);

    cout << "绋嬪簭杩愯鎴愬姛瀹屾垚锛? << endl;
    system("pause"); // 濡傛灉浣跨敤澶栭儴鎺у埗鍙帮紝闃叉绐楀彛涓€闂€岃繃

    return 0;
}