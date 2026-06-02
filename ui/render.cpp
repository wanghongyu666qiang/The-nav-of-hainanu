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
dist[i]=g.adj[start][i];
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
&&g.adj[u][v]!=INT_MAX
&&dist[u]+g.adj[u][v]<dist[v]){
dist[v]=dist[u]+g.adj[u][v];
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
void renderShortestPath(const Graph& walk,const Graph& car,int startIdx,int endIdx,int userType){
//选对应类型的图跑Dijkstra
const Graph& active=(userType==0)?walk:car;
pair<vector<int>,int>res=runDijkstra(active,startIdx,endIdx);
//walk和car共享相同的景点数据,用g做别名保持后面代码不变
const Graph& g=walk;
vector<int>& path=res.first;
int distance=res.second;
//生成HTML
ofstream file("ui/map.html");
if(!file.is_open())return;
{const char bom[]={(char)0xEF,(char)0xBB,(char)0xBF};file.write(bom,3);}//UTF-8 BOM
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
//1)绘制所有道路(步行=实线灰色,车行=虚线深灰)
file<<"<g id=\"roads-layer\">\n";
int n=(int)walk.scenes.size();
for(int i=0;i<n;i++){
for(int j=i+1;j<n;j++){
//步行道
if(walk.adj[i][j]!=INT_MAX){
Pos pi=getPos(walk.scenes[i].id);
Pos pj=getPos(walk.scenes[j].id);
file<<"<line x1=\""<<pi.x<<"\" y1=\""<<pi.y
<<"\" x2=\""<<pj.x<<"\" y2=\""<<pj.y
<<"\" stroke=\"#c0c0c0\" stroke-width=\"1.5\"/>\n";
int mx=(pi.x+pj.x)/2;int my=(pi.y+pj.y)/2;
file<<"<rect x=\""<<mx-10<<"\" y=\""<<my-10<<"\" width=\"20\" height=\"16\" rx=\"4\" fill=\"white\" opacity=\"0.85\"/>\n";
file<<"<text x=\""<<mx<<"\" y=\""<<my+2<<"\" text-anchor=\"middle\" font-size=\"9\" fill=\"#999\">"
<<walk.adj[i][j]<<"</text>\n";
}
//车行道
if(car.adj[i][j]!=INT_MAX){
Pos pi=getPos(car.scenes[i].id);
Pos pj=getPos(car.scenes[j].id);
file<<"<line x1=\""<<pi.x<<"\" y1=\""<<pi.y
<<"\" x2=\""<<pj.x<<"\" y2=\""<<pj.y
<<"\" stroke=\"#a0a0a0\" stroke-width=\"1.5\" stroke-dasharray=\"8,4\"/>\n";
int mx=(pi.x+pj.x)/2;int my=(pi.y+pj.y)/2;
if(walk.adj[i][j]==INT_MAX){
//只有车行道的路段才画车行标签
file<<"<rect x=\""<<mx-10<<"\" y=\""<<my-10<<"\" width=\"20\" height=\"16\" rx=\"4\" fill=\"white\" opacity=\"0.85\"/>\n";
file<<"<text x=\""<<mx<<"\" y=\""<<my+2<<"\" text-anchor=\"middle\" font-size=\"9\" fill=\"#999\">"
<<car.adj[i][j]<<"</text>\n";
}
}
}
}
file<<"</g>\n";
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

//生成交互式地图(可点击景点,JS内置Dijkstra)
void renderInteractiveMap(const Graph& walk,const Graph& car){
const Graph& g=walk;//别名,景点数据两份相同
ofstream file("ui/map.html");
if(!file.is_open())return;
{const char bom[]={(char)0xEF,(char)0xBB,(char)0xBF};file.write(bom,3);}//UTF-8 BOM
//=== HTML头部 ===
file<<"<!DOCTYPE html>\n<html lang=\"zh\">\n<head>\n"
<<"<meta charset=\"UTF-8\">\n"
<<"<meta name=\"viewport\" content=\"width=device-width,initial-scale=1.0\">\n"
<<"<title>海南大学智慧校园导航系统</title>\n"
<<"<style>\n"
<<"*{margin:0;padding:0;box-sizing:border-box}\n"
<<"body{font-family:'Microsoft YaHei',sans-serif;display:flex;height:100vh;background:#f0f2f5;user-select:none}\n"
<<"#map-area{flex:1;display:flex;align-items:center;justify-content:center;background:#fff;margin:12px;border-radius:12px;box-shadow:0 2px 8px rgba(0,0,0,.08);cursor:default}\n"
<<"#panel{width:230px;padding:20px;background:#fff;margin:12px 12px 12px 0;border-radius:12px;box-shadow:0 2px 8px rgba(0,0,0,.08);display:flex;flex-direction:column;gap:14px}\n"
<<"h2{font-size:16px;color:#1a1a2e;border-bottom:2px solid #4a6cf7;padding-bottom:8px}\n"
<<".mode-btn{padding:8px 0;border:2px solid #ddd;border-radius:8px;font-size:13px;cursor:pointer;text-align:center;transition:all .2s;background:#fff}\n"
<<".mode-btn.active{border-color:#4a6cf7;background:#e6f1fb;color:#185fa5;font-weight:bold}\n"
<<".mode-btn:hover{border-color:#4a6cf7}\n"
<<".status-text{font-size:12px;color:#666;line-height:1.8}\n"
<<".status-text b{color:#333}\n"
<<".tag-start{display:inline-block;width:10px;height:10px;border-radius:50%;background:#e24b4b;margin-right:4px;vertical-align:middle}\n"
<<".tag-end{display:inline-block;width:10px;height:10px;border-radius:50%;background:#4a6cf7;margin-right:4px;vertical-align:middle}\n"
<<".btn-action{width:100%;padding:10px;border:none;border-radius:8px;font-size:13px;cursor:pointer}\n"
<<".btn-run{background:#4a6cf7;color:#fff}\n"
<<".btn-run:hover{background:#3b5de7}\n"
<<".btn-reset{background:#f0f0f0;color:#666}\n"
<<".btn-reset:hover{background:#e0e0e0}\n"
<<".result-box{background:#fef5f0;border:1px solid #f0c0a0;border-radius:8px;padding:12px;font-size:12px;line-height:1.8}\n"
<<".result-box .dist{font-size:24px;font-weight:bold;color:#d85a30}\n"
<<".spot{cursor:pointer;transition:r .15s}\n"
<<".spot:hover{filter:brightness(1.15)}\n"
<<".hint{font-size:11px;color:#aaa;text-align:center}\n"
<<"</style>\n</head>\n<body>\n";
//=== SVG地图 ===
file<<"<div id=\"map-area\">\n<svg id=\"map-svg\" viewBox=\"0 0 800 550\" width=\"100%\" height=\"100%\">\n";
file<<"<text x=\"400\" y=\"28\" text-anchor=\"middle\" font-size=\"16\" fill=\"#333\" font-weight=\"bold\">海南大学校园地图 — 点击景点开始导航</text>\n";
//道路(步行=实线,车行=虚线)
file<<"<g id=\"roads-layer\">\n";
int nn=(int)walk.scenes.size();
for(int i=0;i<nn;i++){
for(int j=i+1;j<nn;j++){
//步行道
if(walk.adj[i][j]!=INT_MAX){
Pos pi=getPos(walk.scenes[i].id);
Pos pj=getPos(walk.scenes[j].id);
file<<"<line class=\"road-walk\" data-from=\""<<i<<"\" data-to=\""<<j
<<"\" data-type=\"0\" x1=\""<<pi.x<<"\" y1=\""<<pi.y
<<"\" x2=\""<<pj.x<<"\" y2=\""<<pj.y
<<"\" stroke=\"#c0c0c0\" stroke-width=\"1.5\"/>\n";
int mx=(pi.x+pj.x)/2;int my=(pi.y+pj.y)/2;
file<<"<rect x=\""<<mx-10<<"\" y=\""<<my-10<<"\" width=\"20\" height=\"16\" rx=\"4\" fill=\"white\" opacity=\"0.85\"/>\n";
file<<"<text x=\""<<mx<<"\" y=\""<<my+2<<"\" text-anchor=\"middle\" font-size=\"9\" fill=\"#999\">"
<<walk.adj[i][j]<<"</text>\n";
}
//车行道
if(car.adj[i][j]!=INT_MAX){
Pos pi=getPos(car.scenes[i].id);
Pos pj=getPos(car.scenes[j].id);
file<<"<line class=\"road-car\" data-from=\""<<i<<"\" data-to=\""<<j
<<"\" data-type=\"1\" x1=\""<<pi.x<<"\" y1=\""<<pi.y
<<"\" x2=\""<<pj.x<<"\" y2=\""<<pj.y
<<"\" stroke=\"#a0a0a0\" stroke-width=\"1.5\" stroke-dasharray=\"8,4\"/>\n";
int mx=(pi.x+pj.x)/2;int my=(pi.y+pj.y)/2;
if(walk.adj[i][j]==INT_MAX){
file<<"<rect x=\""<<mx-10<<"\" y=\""<<my-10<<"\" width=\"20\" height=\"16\" rx=\"4\" fill=\"white\" opacity=\"0.85\"/>\n";
file<<"<text x=\""<<mx<<"\" y=\""<<my+2<<"\" text-anchor=\"middle\" font-size=\"9\" fill=\"#999\">"
<<car.adj[i][j]<<"</text>\n";
}
}
}
}
file<<"</g>\n";
//路径高亮层(动态绘制)
file<<"<g id=\"path-layer\"></g>\n";
//景点
file<<"<g id=\"spots-layer\">\n";
for(int i=0;i<(int)g.scenes.size();i++){
Pos p=getPos(g.scenes[i].id);
file<<"<g class=\"spot\" data-index=\""<<i<<"\" onclick=\"selectSpot("<<i<<")\">\n";
file<<"<circle cx=\""<<p.x<<"\" cy=\""<<p.y+1<<"\" r=\"8\" fill=\"rgba(0,0,0,.1)\"/>\n";
file<<"<circle cx=\""<<p.x<<"\" cy=\""<<p.y<<"\" r=\"7\" fill=\"#7f77dd\" stroke=\"#534ab7\" stroke-width=\"2\"/>\n";
file<<"<text x=\""<<p.x<<"\" y=\""<<p.y-14<<"\" text-anchor=\"middle\" font-size=\"12\" fill=\"#333\" font-weight=\"bold\">"
<<toUtf8(g.scenes[i].name)<<"</text>\n";
file<<"<text x=\""<<p.x<<"\" y=\""<<p.y+4<<"\" text-anchor=\"middle\" font-size=\"9\" fill=\"white\" font-weight=\"bold\">"
<<g.scenes[i].id<<"</text>\n";
file<<"</g>\n";
}
file<<"</g>\n";
file<<"</svg>\n</div>\n";
//=== 右侧面板 ===
file<<"<div id=\"panel\">\n";
file<<"<h2>导航控制</h2>\n";
file<<"<div><div id=\"mode-walk\" class=\"mode-btn active\" onclick=\"setMode(0)\">步行模式</div></div>\n";
file<<"<div><div id=\"mode-car\" class=\"mode-btn\" onclick=\"setMode(1)\" style=\"margin-top:6px\">车行模式</div></div>\n";
file<<"<div class=\"status-text\" id=\"status\">"
<<"<div><span class=\"tag-start\"></span>起点：<b id=\"lbl-start\">未选择</b></div>"
<<"<div style=\"margin-top:4px\"><span class=\"tag-end\"></span>终点：<b id=\"lbl-end\">未选择</b></div>"
<<"</div>\n";
//景点简介区(选中起点时显示)
file<<"<div id=\"spot-info\" style=\"display:none;background:#f8f4ff;border:1px solid #d4c4f0;border-radius:8px;padding:10px;font-size:11px;color:#555;line-height:1.5\"></div>\n";
file<<"<div><div class=\"btn-action btn-reset\" onclick=\"resetAll()\">重置选择</div></div>\n";
file<<"<div><div class=\"btn-action btn-allpath\" onclick=\"runDFS()\" style=\"background:#fff;color:#534ab7;border:1.5px solid #7f77dd;margin-bottom:8px\">查询所有路径</div></div>\n";
file<<"<div id=\"result-panel\"><div class=\"hint\">点击地图上的景点选择起点和终点</div></div>\n";
file<<"<div style=\"font-size:10px;color:#bbb;text-align:center;margin-top:auto\">"
<<"实线=步行道 | 虚线=车行道<br>红点=起点 | 蓝点=终点</div>\n";
file<<"</div>\n";
//=== JavaScript(嵌入数据+交互逻辑) ===
file<<"<script>\n";
//嵌入景点数据
file<<"var spots=[";
for(int i=0;i<(int)g.scenes.size();i++){
Pos p=getPos(g.scenes[i].id);
if(i>0)file<<",";
file<<"{id:"<<g.scenes[i].id<<",name:\""<<toUtf8(g.scenes[i].name)
<<"\",desc:\""<<toUtf8(g.scenes[i].description)<<"\",x:"<<p.x<<",y:"<<p.y<<"}";
}
file<<"];\n";
//嵌入邻接矩阵(从两个图分别取步行和车行权重)
file<<"var edges=[";
for(int i=0;i<nn;i++){
if(i>0)file<<",";
file<<"[";
for(int j=0;j<nn;j++){
if(j>0)file<<",";
int ww=walk.adj[i][j];
int cw=car.adj[i][j];
file<<"{w:"<<(ww==INT_MAX?"Infinity":to_string(ww))
<<",c:"<<(cw==INT_MAX?"Infinity":to_string(cw))<<"}";
}
file<<"]";
}
file<<"];\n";
//交互逻辑
file<<"var selectedStart=null,selectedEnd=null,currentMode=0;\n"
<<"function selectSpot(idx){\n"
<<"if(selectedStart===null){selectedStart=idx;updateUI();return;}\n"
<<"if(selectedStart===idx){selectedStart=null;selectedEnd=null;updateUI();return;}\n"
<<"selectedEnd=idx;updateUI();runDijkstra();\n"
<<"}\n"
<<"function setMode(m){\n"
<<"currentMode=m;\n"
<<"document.getElementById('mode-walk').className='mode-btn'+(m===0?' active':'');\n"
<<"document.getElementById('mode-car').className='mode-btn'+(m===1?' active':'');\n"
<<"if(selectedStart!==null&&selectedEnd!==null)runDijkstra();\n"
<<"else updateRoadDisplay();\n"
<<"}\n"
<<"function updateRoadDisplay(){\n"
<<"var lines=document.querySelectorAll('#roads-layer line');\n"
<<"for(var i=0;i<lines.length;i++){\n"
<<"var t=parseInt(lines[i].getAttribute('data-type'));\n"
<<"var show=(currentMode===t);\n"
<<"lines[i].setAttribute('opacity',show?'1':'0.15');\n"
<<"}\n"
<<"}\n"
<<"function updateUI(){\n"
<<"var sp=spots;\n"
<<"document.getElementById('lbl-start').textContent=selectedStart!==null?sp[selectedStart].name:'未选择';\n"
<<"document.getElementById('lbl-end').textContent=selectedEnd!==null?sp[selectedEnd].name:'未选择';\n"
<<"//更新景点颜色\n"
<<"var groups=document.querySelectorAll('#spots-layer .spot');\n"
<<"for(var i=0;i<groups.length;i++){\n"
<<"var c=groups[i].querySelectorAll('circle')[1];\n"
<<"if(i===selectedStart){c.setAttribute('fill','#e24b4b');c.setAttribute('stroke','#a32d2d');c.setAttribute('r','10');}\n"
<<"else if(i===selectedEnd){c.setAttribute('fill','#4a6cf7');c.setAttribute('stroke','#185fa5');c.setAttribute('r','10');}\n"
<<"else{c.setAttribute('fill','#7f77dd');c.setAttribute('stroke','#534ab7');c.setAttribute('r','7');}\n"
<<"}\n"
//显示景点简介
<<"var si=document.getElementById('spot-info');\n"
<<"if(selectedStart!==null){\n"
<<"si.style.display='block';si.innerHTML='<b>'+sp[selectedStart].name+'</b><br>'+sp[selectedStart].desc;\n"
<<"}else{si.style.display='none';}\n"
<<"}\n"
<<"function runDijkstra(){\n"
<<"var s=selectedStart,e=selectedEnd;\n"
<<"if(s===null||e===null)return;\n"
<<"var n=spots.length;\n"
<<"var dist=new Array(n),prev=new Array(n),visited=new Array(n);\n"
<<"for(var i=0;i<n;i++){\n"
<<"var w=currentMode===0?edges[s][i].w:edges[s][i].c;\n"
<<"dist[i]=w;prev[i]=(w<Infinity)?s:-1;visited[i]=false;\n"
<<"}\n"
<<"visited[s]=true;dist[s]=0;prev[s]=-1;\n"
<<"for(var i=0;i<n-1;i++){\n"
<<"var u=-1,mini=Infinity;\n"
<<"for(var j=0;j<n;j++){if(!visited[j]&&dist[j]<mini){mini=dist[j];u=j;}}\n"
<<"if(u===-1)break;visited[u]=true;\n"
<<"for(var v=0;v<n;v++){\n"
<<"if(visited[v])continue;\n"
<<"var ew=currentMode===0?edges[u][v].w:edges[u][v].c;\n"
<<"if(dist[u]!==Infinity&&ew!==Infinity&&dist[u]+ew<dist[v]){\n"
<<"dist[v]=dist[u]+ew;prev[v]=u;\n"
<<"}\n"
<<"}\n"
<<"}\n"
<<"//绘制路径\n"
<<"var layer=document.getElementById('path-layer');\n"
<<"layer.innerHTML='';\n"
<<"if(dist[e]===Infinity){\n"
<<"document.getElementById('result-panel').innerHTML='<div class=\"result-box\" style=\"background:#fcebeb;border-color:#f09595\"><div style=\"color:#e24b4b;font-weight:bold\">无可达路径</div></div>';\n"
<<"return;\n"
<<"}\n"
<<"var path=[];var cur=e;\n"
<<"while(cur!==-1){path.push(cur);cur=prev[cur];}\n"
<<"path.reverse();\n"
<<"//光晕\n"
<<"var pts='';\n"
<<"for(var i=0;i<path.length;i++){pts+=spots[path[i]].x+','+spots[path[i]].y;if(i<path.length-1)pts+=' ';}\n"
<<"layer.innerHTML+='<polyline points=\"'+pts+'\" fill=\"none\" stroke=\"#f5c4b3\" stroke-width=\"10\" stroke-linecap=\"round\" stroke-linejoin=\"round\" opacity=\"0.5\"/>';\n"
<<"layer.innerHTML+='<polyline points=\"'+pts+'\" fill=\"none\" stroke=\"#e24b4b\" stroke-width=\"3.5\" stroke-linecap=\"round\" stroke-linejoin=\"round\"/>';\n"
<<"//方向点\n"
<<"for(var i=0;i<path.length-1;i++){\n"
<<"var mx=(spots[path[i]].x+spots[path[i+1]].x)/2;\n"
<<"var my=(spots[path[i]].y+spots[path[i+1]].y)/2;\n"
<<"layer.innerHTML+='<circle cx=\"'+mx+'\" cy=\"'+my+'\" r=\"4\" fill=\"#fff\" stroke=\"#e24b4b\" stroke-width=\"2\"/>';\n"
<<"}\n"
<<"//结果显示\n"
<<"var html='<div class=\"result-box\"><div class=\"dist\">'+dist[e]+'</div><div style=\"color:#999;font-size:11px;margin-bottom:8px\">最短距离</div><div style=\"font-size:13px;line-height:1.6\">';\n"
<<"for(var i=0;i<path.length;i++){\n"
<<"if(i>0)html+='<span style=\"color:#d85a30;margin:0 4px\">\\u2192</span>';\n"
<<"html+='<strong>'+spots[path[i]].name+'</strong>';\n"
<<"}\n"
<<"html+='</div></div>';\n"
<<"document.getElementById('result-panel').innerHTML=html;\n"
<<"updateUI();\n"
<<"updateRoadDisplay();\n"
<<"}\n"
//DFS查找所有路径
<<"function runDFS(){\n"
<<"var s=selectedStart,e=selectedEnd;\n"
<<"if(s===null||e===null){alert('请先点击地图选择起点和终点');return;}\n"
<<"var n=spots.length;\n"
<<"var visited=new Array(n),path=[],allPaths=[];\n"
<<"for(var i=0;i<n;i++)visited[i]=false;\n"
<<"function dfs(cur,total){\n"
<<"visited[cur]=true;path.push(cur);\n"
<<"if(cur===e){allPaths.push({p:path.slice(),d:total});}\n"
<<"else{\n"
<<"for(var v=0;v<n;v++){\n"
<<"if(visited[v])continue;\n"
<<"var w=currentMode===0?edges[cur][v].w:edges[cur][v].c;\n"
<<"if(w<Infinity)dfs(v,total+w);\n"
<<"}\n"
<<"}\n"
<<"path.pop();visited[cur]=false;\n"
<<"}\n"
<<"dfs(s,0);\n"
//排序并显示
<<"allPaths.sort(function(a,b){return a.d-b.d;});\n"
<<"var maxShow=20;\n"
<<"var html='<div style=\"background:#f0f8ff;border:1px solid #b5d4f4;border-radius:8px;padding:10px;font-size:11px;line-height:1.6;max-height:200px;overflow-y:auto\">';\n"
<<"if(allPaths.length===0){html+='<div style=\"color:#e24b4b\">无可达路径</div>';}\n"
<<"else{\n"
<<"html+='<div style=\"font-weight:bold;margin-bottom:4px;color:#185fa5\">共'+allPaths.length+'条路径'+(allPaths.length>maxShow?('（显示前'+maxShow+'条）'):'')+'</div>';\n"
<<"for(var i=0;i<allPaths.length&&i<maxShow;i++){\n"
<<"html+=(i+1)+'. ';\n"
<<"for(var j=0;j<allPaths[i].p.length;j++){\n"
<<"html+=spots[allPaths[i].p[j]].name;\n"
<<"if(j<allPaths[i].p.length-1)html+=' → ';\n"
<<"}\n"
<<"html+=' <span style=\"color:#999\">('+allPaths[i].d+')</span><br>';\n"
<<"}\n"
<<"}\n"
<<"html+='</div>';\n"
//追加到result-panel后面
<<"document.getElementById('result-panel').innerHTML+=html;\n"
<<"}\n"
<<"function resetAll(){\n"
<<"selectedStart=null;selectedEnd=null;\n"
<<"document.getElementById('lbl-start').textContent='未选择';\n"
<<"document.getElementById('lbl-end').textContent='未选择';\n"
<<"document.getElementById('result-panel').innerHTML='<div class=\"hint\">点击地图上的景点选择起点和终点</div>';\n"
<<"document.getElementById('path-layer').innerHTML='';\n"
<<"document.getElementById('spot-info').style.display='none';\n"
<<"updateUI();\n"
<<"updateRoadDisplay();\n"
<<"}\n"
<<"updateRoadDisplay();\n"
<<"</script>\n</body>\n</html>\n";
file.close();
system("start ui\\map.html");
}
