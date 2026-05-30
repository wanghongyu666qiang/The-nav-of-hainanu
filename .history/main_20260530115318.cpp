#include <iostream>
#include "algorithm/Graph.h"
using namespace std;

int main() {
    Graph g;
    loadScenes(g, "data/scene.txt");
    loadRoads(g, "data/road.txt"); // 鍔犺浇閬撹矾鏁版嵁锛屽垵濮嬪寲閭绘帴鐭╅樀
  while(true) {
        cout<<"娆㈣繋浣跨敤娴峰崡澶у瀵艰埅绯荤粺锛?<<endl;
        cout<<"1. 鏌ヨ鏈€鐭矾寰?<<endl;
        cout<<"2. 澧炲姞鏅偣"<<endl;
        cout<<"3. 鍒犻櫎鏅偣"<<endl;
        cout<<"4. 淇敼鏅偣"<<endl;
        cout<<"5. 澧炲姞閬撹矾"<<endl;
        cout<<"6. 鍒犻櫎閬撹矾"<<endl;
        cout<<"7. 淇敼閬撹矾"<<endl;
        cout<<"8. 閫€鍑虹郴缁?<<endl;
cout<<"璇疯緭鍏ユ搷浣滅紪鍙凤細";
int choice;
cin>>choice;
switch(choice){
    case 1: {
        printScenes(g); // 鎵撳嵃鏅偣鍒楄〃锛屽府鍔╃敤鎴疯緭鍏ユ纭殑缂栧彿
        cout << "璇疯緭鍏ヨ捣鐐瑰拰缁堢偣鐨勭紪鍙蜂互鍙婄敤鎴风被鍨?0姝ヨ,1杞﹁)锛?;
        int startId, endId, userType;
        cin >> startId >> endId >> userType;

        // 鎶婄敤鎴疯緭鍏ョ殑缂栧彿锛圛D锛夎浆鎹负鍐呴儴绱㈠紩
        int n = (int)g.scenes.size();
        int startIndex = -1, endIndex = -1;
        for (int i = 0; i < n; i++) {
            if (g.scenes[i].id == startId) startIndex = i;
            if (g.scenes[i].id == endId) endIndex = i;
        }

        // 鍥為€€绛栫暐锛氬鏋滅敤鎴疯緭鍏ョ殑鏄?0-based 绱㈠紩锛堝父瑙佽瑙ｏ級锛屽皾璇曟寜绱㈠紩鍖归厤
        if (startIndex == -1 && startId >= 0 && startId < n) startIndex = startId;
        if (endIndex == -1 && endId >= 0 && endId < n) endIndex = endId;

        if (startIndex == -1 || endIndex == -1) {
            cout << "杈撳叆鐨勬櫙鐐圭紪鍙蜂笉瀛樺湪锛佽浣跨敤涓嬮潰鐨勭紪鍙锋垨绱㈠紩锛坕d:index锛夛細" << endl;
            for (int i = 0; i < n; ++i) {
                cout << g.scenes[i].id << ":" << i;
                if (i + 1 < n) cout << "  ";
            }
            cout << endl;
        } else {
            // 鐢熸垚瀵瑰簲閫氳鏉冮檺鐨勫浘骞朵紶缁欑畻娉?
            Graph graphToUse = (userType == 0) ? getWalkGraph(g) : getDriveGraph(g);
            getshortestpath(graphToUse, startIndex, endIndex, userType);
        }
        break;
    }
    case 2:{
        cout<<"璇疯緭鍏ユ柊鏅偣鐨勭紪鍙枫€佸悕瀛楀拰鎻忚堪锛?;
        int id;
        string name, desc;
        cin>>id>>name>>desc;
        addScene(g, id, name, desc);
        if (saveScenes(g, "data/scene.txt")) cout<<"鏅偣宸蹭繚瀛樺埌鏂囦欢銆?<<endl;
        else cout<<"淇濆瓨鏅偣澶辫触锛?<<endl;
        break;
    }
    case 3:{
        cout<<"璇疯緭鍏ヨ鍒犻櫎鐨勬櫙鐐圭紪鍙凤細";
        int id;
        cin>>id;
        deleteScene(g, id);
        if (saveScenes(g, "data/scene.txt") && saveRoads(g, "data/road.txt")) cout<<"鍒犻櫎骞朵繚瀛樻垚鍔熴€?<<endl;
        else cout<<"鍒犻櫎鎴栦繚瀛樺け璐ワ紒"<<endl;
        break;
    }
    case 4:{
        cout<<"璇疯緭鍏ヨ淇敼鐨勬櫙鐐圭紪鍙枫€佹柊鍚嶅瓧鍜屾柊鎻忚堪锛?;
        int id;
        string name, desc;
        cin>>id>>name>>desc;
        // 鐩存帴鍦ㄥ唴瀛樹腑淇敼锛岀劧鍚庝繚瀛樺苟閲嶈浇浠ヤ繚璇佷竴鑷存€?
        bool found = false;
        for (auto &s : g.scenes) {
            if (s.id == id) {
                s.name = name;
                s.description = desc;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "鏈壘鍒版寚瀹氭櫙鐐圭紪鍙凤紝淇敼澶辫触銆? << endl;
        } else {
            if (saveScenes(g, "data/scene.txt")) {
                // reload
                g.scenes.clear();
                loadScenes(g, "data/scene.txt");
                loadRoads(g, "data/road.txt");
                cout<<"鏅偣淇敼宸蹭繚瀛樺苟閲嶈浇銆?<<endl;
            } else cout<<"淇濆瓨淇敼澶辫触锛?<<endl;
        }
        break;
    }
    case 5:{
        cout<<"璇疯緭鍏ユ柊閬撹矾鐨勮捣鐐广€佺粓鐐广€佹潈閲嶅拰绫诲瀷锛?;
        int from, to, weight, type;
        cin>>from>>to>>weight>>type;
        addRoad(g, from, to, weight, type);
        if (saveRoads(g, "data/road.txt")) cout<<"閬撹矾宸蹭繚瀛樺埌鏂囦欢銆?<<endl;
        else cout<<"淇濆瓨閬撹矾澶辫触锛?<<endl;
        break;
    }
    case 6:{
        cout<<"璇疯緭鍏ヨ鍒犻櫎鐨勯亾璺捣鐐瑰拰缁堢偣锛?;
        int from, to;
        cin>>from>>to;
        deleteRoad(g, from, to);
        if (saveRoads(g, "data/road.txt")) cout<<"閬撹矾鍒犻櫎骞朵繚瀛樻垚鍔熴€?<<endl;
        else cout<<"鍒犻櫎鎴栦繚瀛橀亾璺け璐ワ紒"<<endl;
        break;
    }
    case 7:{
        cout<<"璇疯緭鍏ヨ淇敼鐨勯亾璺捣鐐广€佺粓鐐广€佹柊鏉冮噸鍜屾柊绫诲瀷锛?;
        int from, to, weight, type;
        cin>>from>>to>>weight>>type;
        // 鐩存帴鍦ㄥ唴瀛樹腑淇敼閬撹矾锛岀劧鍚庝繚瀛樺苟閲嶈浇
        int fromIndex = -1, toIndex = -1;
        for (int i = 0; i < g.scenes.size(); ++i) {
            if (g.scenes[i].id == from) fromIndex = i;
            if (g.scenes[i].id == to) toIndex = i;
        }
        if (fromIndex == -1 || toIndex == -1) {
            cout << "鎵句笉鍒版寚瀹氱殑閬撹矾绔偣锛屼慨鏀瑰け璐ャ€? << endl;
        } else if (g.scenes[fromIndex].edges[toIndex].weight == INT_MAX) {
            cout << "璇ラ亾璺笉瀛樺湪锛屾棤娉曚慨鏀广€? << endl;
        } else {
            g.scenes[fromIndex].edges[toIndex].weight = weight;
            g.scenes[fromIndex].edges[toIndex].roadType = type;
            g.scenes[toIndex].edges[fromIndex].weight = weight;
            g.scenes[toIndex].edges[fromIndex].roadType = type;
            if (saveRoads(g, "data/road.txt")) {
                g.scenes.clear();
                loadScenes(g, "data/scene.txt");
                loadRoads(g, "data/road.txt");
                cout << "閬撹矾淇敼宸蹭繚瀛樺苟閲嶈浇銆? << endl;
            } else cout << "淇濆瓨閬撹矾淇敼澶辫触锛? << endl;
        }
        break;
    }
    case 8:
        cout<<"鎰熻阿浣跨敤锛屽啀瑙侊紒"<<endl;
        return 0;
}
  }
}