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

    // 浜や簰鑿滃崟
    while (true) {
        cout << "\n=== 娴峰崡澶у瀵艰埅绯荤粺 ===" << endl;
        cout << "1. 鏌ヨ鏈€鐭矾寰? << endl;
        cout << "2. 閫€鍑虹郴缁? << endl;
        cout << "璇疯緭鍏ユ偍鐨勯€夋嫨: ";
        
        int choice;
        cin >> choice;

        if (choice == 1) {
            int start, end, type;
            cout << "璇疯緭鍏ヨ捣鐐圭紪鍙? ";
            cin >> start;
            cout << "璇疯緭鍏ョ粓鐐圭紪鍙? ";
            cin >> end;
            cout << "璇疯緭鍏ュ嚭琛屾柟寮?(0浠ｈ〃姝ヨ, 1浠ｈ〃杞﹁): ";
            cin >> type;

            vector<int> path;
            if (type == 0) {
                path = getShortestPath(walkGraph, start, end, 0);
            } else {
                path = getShortestPath(driveGraph, start, end, 1);
            }

            cout << "鏈€鐭矾寰勫寘鍚殑鑺傜偣: ";
            for (int i = 0; i < path.size(); i++) {
                cout << path[i] << " ";
            }
            cout << endl;
        } else if (choice == 2) {
            cout << "鎴愬姛閫€鍑虹郴缁燂紒" << endl;
            break;
        } else {
            cout << "杈撳叆鏈夎锛岃閲嶆柊杈撳叆锛? << endl;
        }
    }

    return 0;
}