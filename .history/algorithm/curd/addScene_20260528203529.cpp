#include "../Graph.h"
#include <algorithm>

using namespace std;

bool addScene(Graph& g, int id, string name, string desc) {
    for (const Scene& s : g.scenes) if (s.id == id) return false;
    
    // 濡傛灉鏄偦鎺ョ煩闃碉紝鍔犲叆鏂版櫙鐐规椂锛岃瀵规墍鏈夌殑鏅偣鎵╁睍涓€涓淮搴︼紝鏈櫙鐐逛篃瑕佸垱寤轰竴涓偅涔堝ぇ鐨勭淮搴?
    int n = g.scenes.size();
    
    // 鎵€鏈変箣鍓嶇殑鏅偣澧炲姞涓€涓幓寰€鏂拌妭鐐圭殑璺紙鍒濆涓轰笉鍙揪锛?
    for (int i = 0; i < n; ++i) {
        g.scenes[i].edges.push_back({id, INT_MAX, -1});
    }

    // 鏂版櫙鐐瑰垵濮嬪寲
    vector<Edge> newEdges(n + 1);
    for (int j = 0; j < n; ++j) {
        newEdges[j] = {g.scenes[j].id, INT_MAX, -1};
    }
    // 鑷繁鍒拌嚜宸辫窛绂讳负 0
    newEdges[n] = {id, 0, -1}; 

    g.scenes.push_back({id, name, desc, newEdges});
    return saveScenes(g, "data/scene.txt");
}
