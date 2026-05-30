#include "../Graph.h"
using namespace std;
#include <iostream>


void printScenes(const Graph& g) {
	cout << "¾°µãÁÐ±í£º" << endl;
	for (const auto& s : g.scenes) {
		cout << s.id << "\t" << s.name << "\t" << s.description << endl;
	}
}
