# -*- coding: utf-8 -*-
import os

ENCODING = 'gbk'

def read_gbk(path):
    with open(path, 'r', encoding=ENCODING) as f:
        return f.read()

def write_gbk(path, content):
    with open(path, 'w', encoding=ENCODING) as f:
        f.write(content)

def replace_in_file(path, old, new):
    c = read_gbk(path)
    if old not in c:
        print(f'WARNING: pattern not found in {path}')
        print(f'Looking for: {repr(old[:80])}')
        return False
    c = c.replace(old, new)
    write_gbk(path, c)
    print(f'Done: {path}')
    return True

# 1. Graph.h
path = 'algorithm/Graph.h'
c = read_gbk(path)
# Find the roadType line and add trafficLights after it
lines = c.split('\n')
new_lines = []
for line in lines:
    new_lines.append(line)
    if 'roadType' in line and 'vector' in line:
        # Extract the comment style from this line
        new_lines.append('std::vector<std::vector<int>>trafficLights;//' + line.split('//')[1] if '//' in line else '')
        # Actually let's just add a simple comment
        new_lines[-1] = 'std::vector<std::vector<int>>trafficLights;//traffic lights count'
c = '\n'.join(new_lines)
# Fix addRoad signature
c = c.replace('bool addRoad(Graph& g,int from,int to,int weight,int type);',
              'bool addRoad(Graph& g,int from,int to,int weight,int type,int lights=0);')
write_gbk(path, c)
print(f'Done: {path}')

# 2. file_io.cpp
path = 'algorithm/curd/file_io.cpp'
c = read_gbk(path)

# Add #include<sstream> after #include<fstream>
c = c.replace('#include<fstream>', '#include<fstream>\n#include<sstream>')

# Add trafficLights init after roadType init in loadScenes
c = c.replace(
    'g.roadType.resize(n,vector<int>(n,-1));',
    'g.roadType.resize(n,vector<int>(n,-1));\ng.trafficLights.resize(n,vector<int>(n,0));'
)

# Replace loadRoads: change the reading loop
old = 'int from,to,weight,type;\nwhile(file>>from>>to>>weight>>type){'
new = 'int from,to,weight,type,lights=0;\nwhile(getline(file,line)){\nif(line.empty()) continue;\nistringstream iss(line);\nlights=0;\nif(!(iss>>from>>to>>weight>>type)) continue;\niss>>lights;'
c = c.replace(old, new)

# Add trafficLights assignment in loadRoads
old = 'g.roadType[fi][ti]=type;\ng.adj[ti][fi]=weight;\ng.roadType[ti][fi]=type;\n}'
new = 'g.roadType[fi][ti]=type;\ng.trafficLights[fi][ti]=lights;\ng.adj[ti][fi]=weight;\ng.roadType[ti][fi]=type;\ng.trafficLights[ti][fi]=lights;\n}'
c = c.replace(old, new)

# Fix saveRoads header
c = c.replace('"\\t\\n";\nint n=(int)g.scenes.size();\nfor(int i=0;i<n;++i){\nfor(int j=i+1;j<n;++j){\nif(g.adj[i][j]!=INT_MAX){\nfile<<g.scenes[i].id<<"\\t"<<g.scenes[j].id<<"\\t"\n<<g.adj[i][j]<<"\\t"<<g.roadType[i][j]',
              '"\\t\\n";\nint n=(int)g.scenes.size();\nfor(int i=0;i<n;++i){\nfor(int j=i+1;j<n;++j){\nif(g.adj[i][j]!=INT_MAX){\nfile<<g.scenes[i].id<<"\\t"<<g.scenes[j].id<<"\\t"\n<<g.adj[i][j]<<"\\t"<<g.roadType[i][j]<<"\\t"<<g.trafficLights[i][j]')

# Fix saveAllRoads
c = c.replace('<<walk.adj[i][j]<<"\\t0\\n";', '<<walk.adj[i][j]<<"\\t0\\t"<<walk.trafficLights[i][j]<<"\\n";')
c = c.replace('<<car.adj[i][j]<<"\\t1\\n";', '<<car.adj[i][j]<<"\\t1\\t"<<car.trafficLights[i][j]<<"\\n";')

write_gbk(path, c)
print(f'Done: {path}')

# 3. Graph.cpp
path = 'algorithm/Graph.cpp'
c = read_gbk(path)
old = 'cout<<g.scenes[result[i]].name<<" ";\n}\ncout<<endl;\n}'
new = '''cout<<g.scenes[result[i]].name<<" ";
}
cout<<endl;
//count traffic lights
int totalLights=0;
for(int i=0;i<(int)result.size()-1;i++){
totalLights+=g.trafficLights[result[i]][result[i+1]];
}
cout<<"traffic lights: "<<totalLights<<endl;
}'''
c = c.replace(old, new)
write_gbk(path, c)
print(f'Done: {path}')

# 4. addRoad.cpp
path = 'algorithm/curd/addRoad.cpp'
c = read_gbk(path)
c = c.replace('bool addRoad(Graph& g,int from,int to,int weight,int type){',
              'bool addRoad(Graph& g,int from,int to,int weight,int type,int lights){')
c = c.replace('g.roadType[fi][ti]=type;\ng.adj[ti][fi]=weight;\ng.roadType[ti][fi]=type;',
              'g.roadType[fi][ti]=type;\ng.trafficLights[fi][ti]=lights;\ng.adj[ti][fi]=weight;\ng.roadType[ti][fi]=type;\ng.trafficLights[ti][fi]=lights;')
write_gbk(path, c)
print(f'Done: {path}')

# 5. deleteRoad.cpp
path = 'algorithm/curd/deleteRoad.cpp'
c = read_gbk(path)
c = c.replace('g.roadType[fi][ti]=-1;\ng.adj[ti][fi]=INT_MAX;\ng.roadType[ti][fi]=-1;',
              'g.roadType[fi][ti]=-1;\ng.trafficLights[fi][ti]=0;\ng.adj[ti][fi]=INT_MAX;\ng.roadType[ti][fi]=-1;\ng.trafficLights[ti][fi]=0;')
write_gbk(path, c)
print(f'Done: {path}')

# 6. addScene.cpp
path = 'algorithm/curd/addScene.cpp'
c = read_gbk(path)
c = c.replace('g.roadType.resize(n+1);\nfor(int i=0;i<=n;++i){\ng.adj[i].resize(n+1,INT_MAX);\ng.roadType[i].resize(n+1,-1);\n}',
              'g.roadType.resize(n+1);\ng.trafficLights.resize(n+1);\nfor(int i=0;i<=n;++i){\ng.adj[i].resize(n+1,INT_MAX);\ng.roadType[i].resize(n+1,-1);\ng.trafficLights[i].resize(n+1,0);\n}')
write_gbk(path, c)
print(f'Done: {path}')

# 7. deleteScene.cpp
path = 'algorithm/curd/deleteScene.cpp'
c = read_gbk(path)
c = c.replace('g.roadType.erase(g.roadType.begin()+index);\nfor(int k=0;k<(int)g.scenes.size();k++){\ng.adj[k].erase(g.adj[k].begin()+index);\ng.roadType[k].erase(g.roadType[k].begin()+index);\n}',
              'g.roadType.erase(g.roadType.begin()+index);\ng.trafficLights.erase(g.trafficLights.begin()+index);\nfor(int k=0;k<(int)g.scenes.size();k++){\ng.adj[k].erase(g.adj[k].begin()+index);\ng.roadType[k].erase(g.roadType[k].begin()+index);\ng.trafficLights[k].erase(g.trafficLights[k].begin()+index);\n}')
write_gbk(path, c)
print(f'Done: {path}')

# 8. main.cpp
path = 'main.cpp'
c = read_gbk(path)
old = 'int from,to,weight,type;cin>>from>>to>>weight>>type;\nGraph& target=(type==0)?gWalk:gCar;\nif(addRoad(target,from,to,weight,type)){'
new = 'int from,to,weight,type,lights=0;cin>>from>>to>>weight>>type;\ncin>>lights;\nGraph& target=(type==0)?gWalk:gCar;\nif(addRoad(target,from,to,weight,type,lights)){'
c = c.replace(old, new)
write_gbk(path, c)
print(f'Done: {path}')

print('\nAll done!')
