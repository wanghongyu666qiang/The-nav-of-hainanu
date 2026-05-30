#include "../Graph.h"
using namespace std;
#include <iostream>

// 绠€鍗曠殑鎵撳嵃鎵€鏈夋櫙鐐癸紝鐢ㄤ簬璋冭瘯鍜岀晫闈㈡樉绀?
void printScenes(const Graph& g) {
	cout << "鏅偣鍒楄〃锛? << endl;
	for (const auto& s : g.scenes) {
		cout << s.id << "\t" << s.name << "\t" << s.description << endl;
	}
}
