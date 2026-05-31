#ifndef RENDER_H
#define RENDER_H
#include "../algorithm/Graph.h"

//生成最短路径地图HTML并在浏览器打开
//g:原始图(含所有道路,用于绘制完整路网)
//startIdx/endIdx:在g.scenes中的索引
//userType:0步行 1车行
void renderShortestPath(const Graph& g,int startIdx,int endIdx,int userType);

#endif
