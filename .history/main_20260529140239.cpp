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
        cout << "璇疯緭鍏ヨ捣鐐瑰拰缁堢偣鐨勭紪鍙蜂互鍙婄敤鎴风被鍨?0姝ヨ,1杞﹁)锛?;
        int startId, endId, userType;
        cin >> startId >> endId >> userType;

        // 杩欓噷灏嗙敤鎴疯緭鍏ョ殑 ID 鍘熸湰杞垚浜?index锛岀劧鍚庡湪绠楁硶澶栭儴浣跨敤
        int startIndex = -1, endIndex = -1;
        for (int i = 0; i < g.scenes.size(); i++) {
            if (g.scenes[i].id == startId) startIndex = i;
            if (g.scenes[i].id == endId) endIndex = i;
        }

        if (startIndex == -1 || endIndex == -1) {
            cout << "杈撳叆鐨勬櫙鐐圭紪鍙蜂笉瀛樺湪锛? << endl;
        } else {
            // 鐢熸垚瀵瑰簲閫氳鏉冮檺鐨勫浘骞朵紶缁欏師灏佷笉鍔ㄧ殑绠楁硶
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
        updateScene(g, id, name, desc);
        if (saveScenes(g, "data/scene.txt")) cout<<"鏅偣淇敼宸蹭繚瀛樸€?<<endl;
        else cout<<"淇濆瓨淇敼澶辫触锛?<<endl;
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
        updateRoad(g, from, to, weight, type);
        if (saveRoads(g, "data/road.txt")) cout<<"閬撹矾淇敼宸蹭繚瀛樸€?<<endl;
        else cout<<"淇濆瓨閬撹矾淇敼澶辫触锛?<<endl;
        break;
    }
    case 8:
        cout<<"鎰熻阿浣跨敤锛屽啀瑙侊紒"<<endl;
        return 0;
}
  }
}