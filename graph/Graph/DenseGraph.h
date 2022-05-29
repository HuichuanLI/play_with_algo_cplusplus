//
// Created by 李汇川 on 2022/5/29.
//

#ifndef PLAY_WITH_ALGO_GRAPH_GRAPH_DENSEGRAPH_H_
#define PLAY_WITH_ALGO_GRAPH_GRAPH_DENSEGRAPH_H_

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

// 稠密图 - 邻接矩阵
class DenseGraph {

 private:
  int n, m;       // 节点数和边数
  bool directed;  // 是否为有向图
  vector<vector<bool>> g; // 图的具体数据

 public:
  // 构造函数
  DenseGraph(int n, bool directed) {
    assert(n >= 0);
    this->n = n;
    this->m = 0;    // 初始化没有任何边
    this->directed = directed;
    // g初始化为n*n的布尔矩阵, 每一个g[i][j]均为false, 表示没有任和边
    g = vector<vector<bool>>(n, vector<bool>(n, false));
  }

  ~DenseGraph() {}

  int V() { return n; } // 返回节点个数
  int E() { return m; } // 返回边的个数

  // 向图中添加一个边
  void addEdge(int v, int w) {

    assert(v >= 0 && v < n);
    assert(w >= 0 && w < n);

    if (hasEdge(v, w))
      return;

    g[v][w] = true;
    if (!directed)
      g[w][v] = true;

    m++;
  }

  // 验证图中是否有从v到w的边
  bool hasEdge(int v, int w) {
    assert(v >= 0 && v < n);
    assert(w >= 0 && w < n);
    return g[v][w];
  }

  // 显示图的信息
  void show() {

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++)
        cout << g[i][j] << "\t";
      cout << endl;
    }
  }

  class adjIterator {
   private:
    DenseGraph &G;  // 图G的引用
    int v;
    int index;
   public:
    // 构造函数
    adjIterator(DenseGraph &graph, int v) : G(graph) {
      assert(v >= 0 && v < G.n);
      this->v = v;
      this->index = -1;   // 索引从-1开始, 因为每次遍历都需要调用一次next()
    }

    ~adjIterator() {}

    // 返回图G中与顶点v相连接的第一个顶点
    int begin() {

      // 索引从-1开始, 因为每次遍历都需要调用一次next()
      index = -1;
      return next();
    }

    // 返回图G中与顶点v相连接的下一个顶点
    int next() {

      // 从当前index开始向后搜索, 直到找到一个g[v][index]为true
      for (index += 1; index < G.V(); index++)
        if (G.g[v][index])
          return index;
      // 若没有顶点和v相连接, 则返回-1
      return -1;
    }
    // 查看是否已经迭代完了图G中与顶点v相连接的所有顶点
    bool end() {
      return index >= G.V();
    }
  };
};

#endif //PLAY_WITH_ALGO_GRAPH_GRAPH_DENSEGRAPH_H_
