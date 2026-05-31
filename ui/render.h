#ifndef RENDER_H
#define RENDER_H
#include "../algorithm/Graph.h"

//生成最短路径地图HTML并在浏览器打开
//walk/car:步行图和车行图(用于绘制路网)
//startIdx/endIdx:在g.scenes中的索引 userType:0步行 1车行
void renderShortestPath(const Graph& walk,const Graph& car,int startIdx,int endIdx,int userType);
//生成交互式地图(可点击景点选起点终点,JS内置Dijkstra)
void renderInteractiveMap(const Graph& walk,const Graph& car);

#endif
