#include "Graph.h"
#include <queue>
#include <iostream>
using namespace std;

void getshortestpath(const Graph& g, int startIndex, int endIndex, int userType) {//采用dijistra算法
    vector<int> result;
    vector<int> path(g.scenes.size()); // 存储路径
    vector<int> dist(g.scenes.size()); // 存储距离
    vector<int> visited(g.scenes.size()); // 存储访问状态,0表示未访问，1表示已访问
    
    //全部用动态数组，防止环境报错
    for(int i=0;i<g.scenes.size();i++){
        dist[i]=g.scenes[startIndex].edges[i].weight; 
        visited[i]=0; 
        if(dist[i]==INT_MAX) path[i]=-1;
        else path[i]=startIndex; 
    }
    visited[startIndex]=1;
    path[startIndex]=-1;//完成初始化
    
    for(int i=0;i<g.scenes.size()-1;i++)
    {
        //找到没被访问的节点距离源点最近的节点
        int mini=INT_MAX;
        int u=-1;
        for(int j=0;j<g.scenes.size();j++)
        {
            if(visited[j]==0&&dist[j]<mini)
            {
                mini=dist[j];
                u=j;//u就是当前距离源点最近的节点
            }
        }//找最近的节点的for
        if(u==-1) break;
        else visited[u]=1;

        //更新u的邻居节点的距离的for
        for(int v=0;v<g.scenes[u].edges.size();v++)
        {
            if(visited[v]==0)
            {
                if(dist[u]!=INT_MAX && g.scenes[u].edges[v].weight!=INT_MAX && dist[u]+g.scenes[u].edges[v].weight<dist[v])
                {
                    dist[v]=dist[u]+g.scenes[u].edges[v].weight;
                    path[v]=u;
                }
            }
        }
    }

    //从end开始回溯路径
    int current=endIndex;//用来储存当前回溯到的节点
    if(dist[endIndex] == INT_MAX) {
        cout << "无法到达目标景点！" << endl;
        return;
    }
    
    while(current!=-1)
    {
        // 这里把内部的 index 转成外部真实 ID，再装入结果打印
        result.push_back(g.scenes[current].id);
        current=path[current];//回溯到上一个节点
    }
    std::reverse(result.begin(),result.end());

    cout<<"最短路径长度为："<<dist[endIndex]<<endl;
    cout<<"路径为：";
    for(int i=0;i<result.size();i++){
        cout<<result[i]<<" ";
    }
    cout<<endl;
}

vector<int> getTSPRoute(const Graph& g, int start, vector<int> targets, int userType) {
    vector<int> route;
    // ... TSP 算法
    return route;
}