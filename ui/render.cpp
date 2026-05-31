#include "render.h"
#include<fstream>
#include<cstdlib>
#include<climits>
#include<algorithm>
#include<windows.h>
#include<vector>
using namespace std;

//GBK字符串转UTF-8(Windows API)
static string toUtf8(const string& gbk){
if(gbk.empty())return gbk;
int wlen=MultiByteToWideChar(CP_ACP,0,gbk.c_str(),-1,NULL,0);
if(wlen<=0)return gbk;
vector<wchar_t>wbuf(wlen);
MultiByteToWideChar(CP_ACP,0,gbk.c_str(),-1,wbuf.data(),wlen);
int ulen=WideCharToMultiByte(CP_UTF8,0,wbuf.data(),-1,NULL,0,NULL,NULL);
if(ulen<=0)return gbk;
vector<char>ubuf(ulen);
WideCharToMultiByte(CP_UTF8,0,wbuf.data(),-1,ubuf.data(),ulen,NULL,NULL);
return string(ubuf.data());
}

//景点坐标映射(SVG画布800x550)
struct Pos{int x;int y;};
static Pos getPos(int id){
switch(id){
case 1:return{120,100};//第一食堂
case 2:return{300,80};//行政楼
case 3:return{480,80};//二号教学楼
case 4:return{400,200};//九教
case 5:return{200,240};//一田
case 6:return{320,360};//书院宿舍楼
case 7:return{530,230};//图书馆
case 8:return{580,370};//南门
case 9:return{150,400};//东门
case 10:return{440,420};//游泳池
default:return{0,0};
}
}

//Dijkstra算法(返回路径+距离,不打印)
static pair<vector<int>,int>runDijkstra(const Graph& g,int start,int end){
int n=(int)g.scenes.size();
vector<int>dist(n,INT_MAX);
vector<int>prev(n,-1);
vector<int>visited(n,0);
//初始化
for(int i=0;i<n;i++){
dist[i]=g.scenes[start].edges[i].weight;
if(dist[i]!=INT_MAX)prev[i]=start;
}
visited[start]=1;
prev[start]=-1;
dist[start]=0;
//主循环
for(int i=0;i<n-1;i++){
int u=-1;
int mini=INT_MAX;
for(int j=0;j<n;j++){
if(!visited[j]&&dist[j]<mini){mini=dist[j];u=j;}
}
if(u==-1)break;
visited[u]=1;
for(int v=0;v<n;v++){
if(!visited[v]&&dist[u]!=INT_MAX
&&g.scenes[u].edges[v].weight!=INT_MAX
&&dist[u]+g.scenes[u].edges[v].weight<dist[v]){
dist[v]=dist[u]+g.scenes[u].edges[v].weight;
prev[v]=u;
}
}
}
//回溯路径
vector<int>path;
if(dist[end]==INT_MAX)return{path,INT_MAX};
int cur=end;
while(cur!=-1){path.push_back(cur);cur=prev[cur];}
reverse(path.begin(),path.end());
return{path,dist[end]};
}

//生成地图HTML并在浏览器打开
void renderShortestPath(const Graph& g,int startIdx,int endIdx,int userType){
//用过滤后的图跑Dijkstra
Graph fg=getFilteredGraph(g,userType);
pair<vector<int>,int>res=runDijkstra(fg,startIdx,endIdx);
vector<int>& path=res.first;
int distance=res.second;
//生成HTML
ofstream file("ui/map.html");
if(!file.is_open())return;
file<<"<!DOCTYPE html>\n<html lang=\"zh\">\n<head>\n"
<<"<meta charset=\"UTF-8\">\n"
<<"<meta name=\"viewport\" content=\"width=device-width,initial-scale=1.0\">\n"
<<"<title>海南大学智慧校园导航系统</title>\n"
<<"<style>\n"
<<"*{margin:0;padding:0;box-sizing:border-box}\n"
<<"body{font-family:'Microsoft YaHei',sans-serif;display:flex;height:100vh;background:#f0f2f5}\n"
<<"#map-area{flex:1;display:flex;align-items:center;justify-content:center;background:#fff;margin:12px;border-radius:12px;box-shadow:0 2px 8px rgba(0,0,0,.08)}\n"
<<"#panel{width:230px;padding:20px;background:#fff;margin:12px 12px 12px 0;border-radius:12px;box-shadow:0 2px 8px rgba(0,0,0,.08);display:flex;flex-direction:column;gap:14px}\n"
<<"h2{font-size:16px;color:#1a1a2e;border-bottom:2px solid #4a6cf7;padding-bottom:8px}\n"
<<".mode-tag{display:inline-block;padding:4px 10px;border-radius:12px;font-size:11px;font-weight:500}\n"
<<".mode-walk{background:#e6f7e6;color:#3b6d11}\n"
<<".mode-car{background:#e6f1fb;color:#185fa5}\n"
<<".result-box{background:#fef5f0;border:1px solid #f0c0a0;border-radius:8px;padding:12px;font-size:12px;line-height:1.8}\n"
<<".result-box .dist{font-size:24px;font-weight:bold;color:#d85a30}\n"
<<".legend{font-size:11px;color:#888;display:flex;align-items:center;gap:6px}\n"
<<".legend-dot{display:inline-block;width:10px;height:10px;border-radius:50%}\n"
<<"</style>\n</head>\n<body>\n";
//SVG地图
file<<"<div id=\"map-area\">\n<svg viewBox=\"0 0 800 550\" width=\"100%\" height=\"100%\">\n";
//地图标题
file<<"<text x=\"400\" y=\"30\" text-anchor=\"middle\" font-size=\"16\" fill=\"#333\" font-weight=\"bold\">海南大学校园地图</text>\n";
//1)绘制所有道路
for(int i=0;i<(int)g.scenes.size();i++){
for(int j=i+1;j<(int)g.scenes.size();j++){
if(g.scenes[i].edges[j].weight==INT_MAX)continue;
Pos pi=getPos(g.scenes[i].id);
Pos pj=getPos(g.scenes[j].id);
int type=g.scenes[i].edges[j].roadType;
string color=(type==0)?"#c0c0c0":"#a0a0a0";
string dash=(type==1)?"stroke-dasharray=\"8,4\"":"";
file<<"<line x1=\""<<pi.x<<"\" y1=\""<<pi.y
<<"\" x2=\""<<pj.x<<"\" y2=\""<<pj.y
<<"\" stroke=\""<<color<<"\" stroke-width=\"1.5\" "<<dash<<"/>\n";
//距离标签
int mx=(pi.x+pj.x)/2;
int my=(pi.y+pj.y)/2;
file<<"<rect x=\""<<mx-10<<"\" y=\""<<my-10<<"\" width=\"20\" height=\"16\" rx=\"4\" fill=\"white\" opacity=\"0.85\"/>\n";
file<<"<text x=\""<<mx<<"\" y=\""<<my+2<<"\" text-anchor=\"middle\" font-size=\"9\" fill=\"#999\">"
<<g.scenes[i].edges[j].weight<<"</text>\n";
}
}
//2)高亮最短路径
if(distance!=INT_MAX&&path.size()>=2){
//路径底色(更宽的光晕)
file<<"<polyline points=\"";
for(int i=0;i<(int)path.size();i++){
Pos p=getPos(g.scenes[path[i]].id);
file<<p.x<<","<<p.y;
if(i<(int)path.size()-1)file<<" ";
}
file<<"\" fill=\"none\" stroke=\"#f5c4b3\" stroke-width=\"10\" stroke-linecap=\"round\" stroke-linejoin=\"round\" opacity=\"0.5\"/>\n";
//路径主线
file<<"<polyline points=\"";
for(int i=0;i<(int)path.size();i++){
Pos p=getPos(g.scenes[path[i]].id);
file<<p.x<<","<<p.y;
if(i<(int)path.size()-1)file<<" ";
}
file<<"\" fill=\"none\" stroke=\"#e24b4b\" stroke-width=\"3.5\" stroke-linecap=\"round\" stroke-linejoin=\"round\"/>\n";
//方向箭头(线段中点)
for(int i=0;i<(int)path.size()-1;i++){
Pos p1=getPos(g.scenes[path[i]].id);
Pos p2=getPos(g.scenes[path[i+1]].id);
int mx=(p1.x+p2.x)/2;
int my=(p1.y+p2.y)/2;
file<<"<circle cx=\""<<mx<<"\" cy=\""<<my<<"\" r=\"4\" fill=\"#fff\" stroke=\"#e24b4b\" stroke-width=\"2\"/>\n";
}
}
//3)绘制景点
for(int i=0;i<(int)g.scenes.size();i++){
Pos p=getPos(g.scenes[i].id);
bool isStart=(i==startIdx);
bool isEnd=(i==endIdx);
bool onPath=false;
for(int k=0;k<(int)path.size();k++)if(path[k]==i){onPath=true;break;}
string fill,stroke;
int r;
if(isStart){fill="#e24b4b";stroke="#a32d2d";r=11;}
else if(isEnd){fill="#4a6cf7";stroke="#185fa5";r=11;}
else if(onPath){fill="#f0997b";stroke="#d85a30";r=8;}
else{fill="#7f77dd";stroke="#534ab7";r=7;}
//阴影
file<<"<circle cx=\""<<p.x<<"\" cy=\""<<p.y+1<<"\" r=\""<<r<<"\" fill=\"rgba(0,0,0,.1)\"/>\n";
//主体
file<<"<circle cx=\""<<p.x<<"\" cy=\""<<p.y<<"\" r=\""<<r
<<"\" fill=\""<<fill<<"\" stroke=\""<<stroke<<"\" stroke-width=\"2\"/>\n";
//标签
file<<"<text x=\""<<p.x<<"\" y=\""<<p.y-16<<"\" text-anchor=\"middle\" font-size=\"12\" fill=\"#333\" font-weight=\"bold\">"
<<toUtf8(g.scenes[i].name)<<"</text>\n";
//ID小标
file<<"<text x=\""<<p.x<<"\" y=\""<<p.y+4<<"\" text-anchor=\"middle\" font-size=\"9\" fill=\"white\" font-weight=\"bold\">"
<<g.scenes[i].id<<"</text>\n";
}
file<<"</svg>\n</div>\n";
//右侧信息面板
file<<"<div id=\"panel\">\n";
file<<"<h2>导航结果</h2>\n";
file<<"<div><span class=\"mode-tag " <<(userType==0?"mode-walk":"mode-car")
<<"\">"<<(userType==0?"步行模式":"车行模式")<<"</span></div>\n";
file<<"<div class=\"legend\">"
<<"<span class=\"legend-dot\" style=\"background:#e24b4b\"></span>起点："
<<toUtf8(g.scenes[startIdx].name)<<"</div>\n";
file<<"<div class=\"legend\">"
<<"<span class=\"legend-dot\" style=\"background:#4a6cf7\"></span>终点："
<<toUtf8(g.scenes[endIdx].name)<<"</div>\n";
if(distance==INT_MAX){
file<<"<div class=\"result-box\" style=\"background:#fcebeb;border-color:#f09595\">"
<<"<div style=\"color:#e24b4b;font-weight:bold\">无可达路径</div>"
<<"<div style=\"color:#999;font-size:11px\">该模式下起点与终点不连通</div></div>\n";
}else{
file<<"<div class=\"result-box\">"
<<"<div class=\"dist\">"<<distance<<"</div>"
<<"<div style=\"color:#999;font-size:11px;margin-bottom:8px\">最短距离</div>"
<<"<div style=\"font-size:13px;line-height:1.6\">";
for(int i=0;i<(int)path.size();i++){
if(i>0)file<<"<span style=\"color:#d85a30;margin:0 4px\">→</span>";
file<<"<strong>"<<toUtf8(g.scenes[path[i]].name)<<"</strong>";
}
file<<"</div></div>\n";
}
file<<"<div style=\"font-size:10px;color:#bbb;text-align:center;margin-top:auto\">"
<<"实线=步行道 | 虚线=车行道</div>\n";
file<<"</div>\n</body>\n</html>\n";
file.close();
//用浏览器打开
system("start ui\\map.html");
}
