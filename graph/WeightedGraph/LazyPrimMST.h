//
// Created by 李汇川 on 2022/5/29.
//

#ifndef PLAY_WITH_ALGO_GRAPH_WEIGHTEDGRAPH_LAZYPRIMMST_H_
#define PLAY_WITH_ALGO_GRAPH_WEIGHTEDGRAPH_LAZYPRIMMST_H_
#include <iostream>
#include <vector>
#include <cassert>
#include "Edge.h"
#include "MinHeap.h"

using namespace std;
template<typename Graph, typename Weight>
class LazyPrimMST {
 private:
  Graph &G;
  MinHeap<Edge<Weight> > pq;
  bool *marked;
  vector<Edge<Weight> > mst;
  Weight mstWeight;
  // 访问节点v
  void visit(int v) {

    assert(!marked[v]);
    marked[v] = true;
    // 将和节点v相连接的所有未访问的边放入最小堆中
    typename Graph::adjIterator adj(G, v);
    for (Edge<Weight> *e = adj.begin(); !adj.end(); e = adj.next())
      if (!marked[e->other(v)])
        pq.insert(*e);

  }
 public:
  LazyPrimMST(Graph &graph) : G(graph), pq(MinHeap<Edge<Weight> >(graph.E())) {
    marked = new bool[G.V()];
    // 算法初始化
    marked = new bool[G.V()];
    for (int i = 0; i < G.V(); i++)
      marked[i] = false;
    mst.clear();

    // Lazy Prim
    visit(0);
    while (!pq.isEmpty()) {
      // 使用最小堆找出已经访问的边中权值最小的边
      Edge<Weight> e = pq.extractMin();
      // 如果这条边的两端都已经访问过了, 则扔掉这条边
      if (marked[e.v()] == marked[e.w()])
        continue;
      mst.push_back(e);
      if (!marked[e.v()])
        visit(e.v());
      else
        visit(e.w());
    }
    // 计算最小生成树的权值
    mstWeight = mst[0].wt();
    for (int i = 1; i < mst.size(); i++)
      mstWeight += mst[i].wt();
  }

  // 析构函数
  ~LazyPrimMST() {
    delete[] marked;
  }
  // 返回最小生成树的所有边
  vector<Edge<Weight> > mstEdges() {
    return mst;
  };

  // 返回最小生成树的权值
  Weight result() {
    return mstWeight;
  };
};

#endif //PLAY_WITH_ALGO_GRAPH_WEIGHTEDGRAPH_LAZYPRIMMST_H_
