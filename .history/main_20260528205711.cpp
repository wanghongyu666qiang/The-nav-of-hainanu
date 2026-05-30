#include <iostream>
#include "algorithm/Graph.h"
using namespace std;

int main() {
    Graph g;
    loadScenes(g, "data/scene.txt");
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
        
        Graph graphToUse = (userType == 0) ? getWalkGraph(g) : getDriveGraph(g);
        
        // ================== 銆愭牳蹇冿細澶栭儴澶勭悊 ID 杞?Index銆?==================
        int startIndex = -1, endIndex = -1;
        for (int i = 0; i < graphToUse.scenes.size(); i++) {
            if (graphToUse.scenes[i].id == startId) startIndex = i;
            if (graphToUse.scenes[i].id == endId) endIndex = i;
        }
        
        if (startIndex == -1 || endIndex == -1) {
            cout << "杈撳叆鐨勬櫙鐐圭紪鍙蜂笉瀛樺湪锛? << endl;
        } else {
            getshortestpath(graphToUse, startIndex, endIndex, userType);
        }
        break;
    }
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        cout<<"鎰熻阿浣跨敤锛屽啀瑙侊紒"<<endl;
        return 0;
}
  }
}