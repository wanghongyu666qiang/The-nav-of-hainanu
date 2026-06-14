# -*- coding: utf-8 -*-
import os

ENCODING = 'gbk'

def read_gbk(path):
    with open(path, 'r', encoding=ENCODING) as f:
        return f.read()

def write_gbk(path, content):
    with open(path, 'w', encoding=ENCODING) as f:
        f.write(content)

# 1. Graph.h - add trafficLights matrix and update addRoad signature
path = 'algorithm/Graph.h'
c = read_gbk(path)
c = c.replace(
    'std::vector<std::vector<int>>roadType;//存储道路类型，-1=无路,0=步行,1=车行，2=两者皆可\n};',
    'std::vector<std::vector<int>>roadType;//存储道路类型，-1=无路,0=步行,1=车行，2=两者皆可\nstd::vector<std::vector<int>>trafficLights;//存储红绿灯数量\n};'
)
c = c.replace(
    'bool addRoad(Graph& g,int from,int to,int weight,int type);',
    'bool addRoad(Graph& g,int from,int to,int weight,int type,int lights=0);'
)
write_gbk(path, c)
print(f'Done: {path}')

# 2. file_io.cpp - add sstream, init trafficLights, read/write lights
path = 'algorithm/curd/file_io.cpp'
c = read_gbk(path)

# Add #include<sstream>
c = c.replace('#include<fstream>', '#include<fstream>\n#include<sstream>')

# Init trafficLights in loadScenes
c = c.replace(
    'g.roadType.resize(n,vector<int>(n,-1));\nfor(int i=0;i<n;++i){',
    'g.roadType.resize(n,vector<int>(n,-1));\ng.trafficLights.resize(n,vector<int>(n,0));\nfor(int i=0;i<n;++i){'
)

# Replace loadRoads function body
old_loadroads = '''int from,to,weight,type;
while(file>>from>>to>>weight>>type){
if(roadType!=-1&&type!=roadType)continue;
int fi=getIdIndex(g.scenes,from);
int ti=getIdIndex(g.scenes,to);
if(fi==-1||ti==-1)continue;
//双向赋值到邻接矩阵
g.adj[fi][ti]=weight;
g.roadType[fi][ti]=type;
g.adj[ti][fi]=weight;
g.roadType[ti][fi]=type;
}'''

new_loadroads = '''int from,to,weight,type,lights=0;
while(getline(file,line)){
if(line.empty()) continue;
istringstream iss(line);
lights=0;
if(!(iss>>from>>to>>weight>>type)) continue;
iss>>lights;
if(roadType!=-1&&type!=roadType)continue;
int fi=getIdIndex(g.scenes,from);
int ti=getIdIndex(g.scenes,to);
if(fi==-1||ti==-1)continue;
//双向赋值到邻接矩阵
g.adj[fi][ti]=weight;
g.roadType[fi][ti]=type;
g.trafficLights[fi][ti]=lights;
g.adj[ti][fi]=weight;
g.roadType[ti][fi]=type;
g.trafficLights[ti][fi]=lights;
}'''
c = c.replace(old_loadroads, new_loadroads)

# Replace saveRoads
c = c.replace(
    'file<<"起点\\t终点\\t距离\\t类型\\n";',
    'file<<"起点\\t终点\\t距离\\t类型\\t红绿灯\\n";'
)
c = c.replace(
    '<<g.adj[i][j]<<"\\t"<<g.roadType[i][j]<<"\\n";',
    '<<g.adj[i][j]<<"\\t"<<g.roadType[i][j]<<"\\t"<<g.trafficLights[i][j]<<"\\n";'
)

# Replace saveAllRoads
c = c.replace(
    'file<<"起点\\t终点\\t距离\\t类型\\n";\nint n=(int)walk.scenes.size();',
    'file<<"起点\\t终点\\t距离\\t类型\\t红绿灯\\n";\nint n=(int)walk.scenes.size();'
)
c = c.replace(
    '<<walk.adj[i][j]<<"\\t0\\n";',
    '<<walk.adj[i][j]<<"\\t0\\t"<<walk.trafficLights[i][j]<<"\\n";'
)
c = c.replace(
    '<<car.adj[i][j]<<"\\t1\\n";',
    '<<car.adj[i][j]<<"\\t1\\t"<<car.trafficLights[i][j]<<"\\n";'
)

write_gbk(path, c)
print(f'Done: {path}')

# 3. Graph.cpp - add traffic light count output
path = 'algorithm/Graph.cpp'
c = read_gbk(path)

old_output = '''cout<<"最短路径长度为："<<dist[end]<<endl;
cout<<"路径为：";
for(int i=0;i<result.size();i++){
cout<<g.scenes[result[i]].name<<" ";
}
cout<<endl;
}'''

new_output = '''cout<<"最短路径长度为："<<dist[end]<<endl;
cout<<"路径为：";
for(int i=0;i<result.size();i++){
cout<<g.scenes[result[i]].name<<" ";
}
cout<<endl;
//统计红绿灯数量
int totalLights=0;
for(int i=0;i<(int)result.size()-1;i++){
totalLights+=g.trafficLights[result[i]][result[i+1]];
}
cout<<"红绿灯数量："<<totalLights<<endl;
}'''
c = c.replace(old_output, new_output)
write_gbk(path, c)
print(f'Done: {path}')

# 4. addRoad.cpp - add lights parameter
path = 'algorithm/curd/addRoad.cpp'
c = read_gbk(path)
c = c.replace(
    'bool addRoad(Graph& g,int from,int to,int weight,int type){',
    'bool addRoad(Graph& g,int from,int to,int weight,int type,int lights){'
)
c = c.replace(
    'g.roadType[fi][ti]=type;\ng.adj[ti][fi]=weight;\ng.roadType[ti][fi]=type;',
    'g.roadType[fi][ti]=type;\ng.trafficLights[fi][ti]=lights;\ng.adj[ti][fi]=weight;\ng.roadType[ti][fi]=type;\ng.trafficLights[ti][fi]=lights;'
)
write_gbk(path, c)
print(f'Done: {path}')

# 5. deleteRoad.cpp - clear trafficLights
path = 'algorithm/curd/deleteRoad.cpp'
c = read_gbk(path)
c = c.replace(
    'g.roadType[fi][ti]=-1;\ng.adj[ti][fi]=INT_MAX;\ng.roadType[ti][fi]=-1;',
    'g.roadType[fi][ti]=-1;\ng.trafficLights[fi][ti]=0;\ng.adj[ti][fi]=INT_MAX;\ng.roadType[ti][fi]=-1;\ng.trafficLights[ti][fi]=0;'
)
write_gbk(path, c)
print(f'Done: {path}')

# 6. addScene.cpp - resize trafficLights
path = 'algorithm/curd/addScene.cpp'
c = read_gbk(path)
c = c.replace(
    'g.roadType.resize(n+1);\nfor(int i=0;i<=n;++i){\ng.adj[i].resize(n+1,INT_MAX);\ng.roadType[i].resize(n+1,-1);\n}',
    'g.roadType.resize(n+1);\ng.trafficLights.resize(n+1);\nfor(int i=0;i<=n;++i){\ng.adj[i].resize(n+1,INT_MAX);\ng.roadType[i].resize(n+1,-1);\ng.trafficLights[i].resize(n+1,0);\n}'
)
write_gbk(path, c)
print(f'Done: {path}')

# 7. deleteScene.cpp - erase trafficLights
path = 'algorithm/curd/deleteScene.cpp'
c = read_gbk(path)
c = c.replace(
    'g.roadType.erase(g.roadType.begin()+index);\nfor(int k=0;k<(int)g.scenes.size();k++){\ng.adj[k].erase(g.adj[k].begin()+index);\ng.roadType[k].erase(g.roadType[k].begin()+index);\n}',
    'g.roadType.erase(g.roadType.begin()+index);\ng.trafficLights.erase(g.trafficLights.begin()+index);\nfor(int k=0;k<(int)g.scenes.size();k++){\ng.adj[k].erase(g.adj[k].begin()+index);\ng.roadType[k].erase(g.roadType[k].begin()+index);\ng.trafficLights[k].erase(g.trafficLights[k].begin()+index);\n}'
)
write_gbk(path, c)
print(f'Done: {path}')

# 8. main.cpp - update case 9
path = 'main.cpp'
c = read_gbk(path)
c = c.replace(
    'cout<<"请输入道路的起点编号、终点编号、权重和类型(0步行,1车行)：";\nint from,to,weight,type;cin>>from>>to>>weight>>type;\nGraph& target=(type==0)?gWalk:gCar;\nif(addRoad(target,from,to,weight,type)){',
    'cout<<"请输入道路的起点编号、终点编号、权重、类型(0步行,1车行)和红绿灯数量：";\nint from,to,weight,type,lights=0;cin>>from>>to>>weight>>type;\ncin>>lights;\nGraph& target=(type==0)?gWalk:gCar;\nif(addRoad(target,from,to,weight,type,lights)){'
)
write_gbk(path, c)
print(f'Done: {path}')

print('\nAll done!')
