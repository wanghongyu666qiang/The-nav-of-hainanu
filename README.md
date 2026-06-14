## 海南大学导航系统

### 运行命令

```bash
g++ main.cpp algorithm/Graph.cpp algorithm/curd/*.cpp -o main.exe && main.exe
```

### 系统概述

海南大学多校区（海甸、观澜湖、儋州）校园导航系统，采用 C++ 控制台 + HTML 可视化双端架构。核心使用 **Dijkstra 算法**计算最短路径，**DFS 回溯算法**枚举所有路径及满足条件（必经地点）的路径，并实现步行/车行**双图分离**设计。

---

### 系统架构

```
The_navigation_of_hainanu/
├── data/                        <-- 数据库
│   ├── scene.txt                (20个景点: 编号、名称、描述)
│   └── road.txt                 (50条道路: 起点、终点、距离、类型、红绿灯数)
│
├── algorithm/                   <-- 核心引擎库
│   ├── Graph.h                  (数据结构定义 + 所有函数声明)
│   ├── Graph.cpp                (Dijkstra最短路径 + DFS路径枚举 + 条件路径)
│   └── curd/
│       ├── file_io.cpp          (景点/道路的读写 + 双图合并保存)
│       ├── addScene.cpp         (添加景点)
│       ├── deleteScene.cpp      (删除景点)
│       ├── addRoad.cpp          (添加道路)
│       ├── deleteRoad.cpp       (删除道路)
│       └── printscene.cpp       (打印景点列表)
│
├── ui/                          <-- 可视化前端
│   ├── selection.html           (校区选择页)
│   ├── map_haidian.html         (海甸校区地图)
│   ├── guanlanhu.html           (观澜湖校区地图)
│   └── zhanzuo.html             (儋州校区地图)
│
└── main.cpp                     <-- 程序入口（控制台交互菜单）
```

---

### 核心数据结构

```cpp
struct Scene {
    int id;                    // 景点编号
    std::string name;          // 景点名称
    std::string description;   // 景点简介
};

struct Graph {
    std::vector<Scene> scenes;             // 景点列表
    std::vector<std::vector<int>> adj;     // 邻接矩阵（存储权重，INT_MAX=不连通）
    std::vector<std::vector<int>> roadType; // -1=无路, 0=步行, 1=车行, 2=皆可
    std::vector<std::vector<int>> trafficLights; // 红绿灯数量
};
```

### 双图架构

邻接矩阵每个位置只能存一条边，但同一对景点间可能同时存在步行道和车行道。解决方案：

- `gWalk` — 仅加载步行道（roadType=0），用于步行导航
- `gCar` — 仅加载车行道（roadType=1），用于车行导航

两个图共享景点数据，道路数据各自独立，互不覆盖。

---

### 功能列表

| 编号 | 功能 | 说明 |
|------|------|------|
| 0 | 打开地图 | 在浏览器中打开校区选择页面 |
| 1 | 最短路径查询 | Dijkstra 算法，区分步行/车行，输出距离+路径+红绿灯数 |
| 2 | 所有路径查询 | DFS 回溯枚举两景点间所有简单路径 |
| 3 | 满足条件的路径 | 指定必经地点，DFS 筛选经过所有必经点的路径 |
| 4 | 景点信息查询 | 列出所有景点及简介 |
| 5 | 多目的地最短距离 | 输入一个景点编号，输出到所有其他景点的最短距离 |
| 6-8 | 景点管理 | 增加/删除/修改景点 |
| 9-11 | 道路管理 | 增加/删除/修改道路（区分步行和车行） |
| 12 | 退出系统 | — |

---

### 算法说明

#### Dijkstra 最短路径（O(n?)）

经典贪心最短路径算法，维护距离数组 `dist[]` 和路径前驱数组 `path[]`。每轮选择未访问的最近顶点更新邻居距离。健壮性处理：加法前判断 `INT_MAX` 防溢出。

#### DFS 路径枚举（O(V+E)）

深度优先搜索 + 回溯，递归探索所有不经过重复顶点的路径。分为两种模式：

- **普通模式**（`what=0`）：打印所有路径及距离
- **条件模式**（`what=1`）：用哈希表 `unordered_map<int,int>` 记录必经地点，路径遍历后判断是否全部经过

---

### 数据规模

- **校区**：海甸（主）、观澜湖、儋州，共 3 个可导航校区
- **景点**：20 个（海甸 10 + 观澜湖 5 + 儋州 5）
- **道路**：50 条（校内道路 + 校区间车行道路）

---

### 编译环境

- **编译器**：g++ (MinGW-w64)，C++11 标准
- **系统**：Windows 10/11
- **浏览器**：Chrome / Edge（查看 HTML 地图）
