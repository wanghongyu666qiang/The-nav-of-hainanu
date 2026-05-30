#include <iostream>
#include "algorithm/Graph.h"

using namespace std;

int main() {
    // 1. 澹版槑涓€涓寘鍚簡鏅偣鍜岃竟鐨勫浘鍙橀噺
    Graph myGraph; 

    // 2. 璋冪敤鍑芥暟鎶婃暟鎹杩涘幓 (鎶?myGraph 浣滀负鍙傛暟浼犺繘鍘诲～婊?
    if (!loadScenes(myGraph, "data/scene.txt")) {
        cout << "銆愪弗閲嶉敊璇€戞棤娉曡鍙?data/scene.txt锛佽纭繚鎮ㄥ湪椤圭洰鐨勬牴鐩綍杩愯绋嬪簭锛岃€屼笉鏄?output 鏂囦欢澶广€? << endl;
        system("pause");
        return -1;
    }
    if (!loadRoads(myGraph, "data/road.txt")) {
        cout << "銆愪弗閲嶉敊璇€戞棤娉曡鍙?data/road.txt锛? << endl;
        system("pause");
        return -1;
    }

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

            // 鐢变簬鏅偣 ID 鏄敤鎴疯緭鍏ョ殑锛?~10锛夛紝鑰?getShortestPath 鏄熀浜庢暟缁勪笅鏍囷紙0~9锛夎绠楃殑
            // 鎵€浠ユ垜浠渶瑕佸皢浼犲叆鐨?ID 杞崲涓烘暟缁勭储寮曡繘琛岃绠楋紝瀹屾垚鍚庡啀鎶婄粨鏋滆浆鎹㈠洖鐪熷疄 ID锛?
            int startIndex = -1, endIndex = -1;
            for (size_t i = 0; i < myGraph.scenes.size(); i++) {
                if (myGraph.scenes[i].id == start) startIndex = i;
                if (myGraph.scenes[i].id == end) endIndex = i;
            }

            if (startIndex == -1 || endIndex == -1) {
                cout << "鎮ㄨ緭鍏ョ殑鏅偣缂栧彿涓嶅瓨鍦紝璇烽噸鏂拌緭鍏ワ紒" << endl;
                continue;
            }

            vector<int> path;
            if (type == 0) {
                path = getShortestPath(walkGraph, startIndex, endIndex, 0);
            } else {
                path = getShortestPath(driveGraph, startIndex, endIndex, 1);
            }

            if (path.empty() || path[0] == -1) {
                cout << "鎶辨瓑锛屾棤娉曟壘鍒颁粠璧风偣鍒扮粓鐐圭殑璇ョ鍑鸿绫诲瀷璺緞锛? << endl;
            } else {
                cout << "鏈€鐭矾寰勫寘鍚殑鑺傜偣: ";
                for (size_t i = 0; i < path.size(); i++) {
                    // 缁撴灉鏄粠 path 閲屽嚭鏉ョ殑绱㈠紩锛岃杞洖鏅偣鐨勭湡瀹?ID
                    cout << myGraph.scenes[path[i]].id << (i == path.size() - 1 ? "" : " -> ");
                }
                cout << endl;
            }
        } else if (choice == 2) {
            cout << "鎴愬姛閫€鍑虹郴缁燂紒" << endl;
            break;
        } else {
            cout << "杈撳叆鏈夎锛岃閲嶆柊杈撳叆锛? << endl;
        }
    }

    return 0;
}