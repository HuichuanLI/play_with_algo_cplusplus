//
// Created by 李汇川 on 2022/5/29.
//
#include <iostream>
#include <iomanip>
#include "DenseGraph.h"
#include "SparseGraph.h"
#include "ReadGraph.h"
#include "LazyPrimMST.h"
#include "KruskalMST.h"
using namespace std;

// 测试有权图和有权图的读取
int main() {

  string filename = "/Users/hui/Desktop/c++/play_with_algo/graph/WeightedGraph/testG1.txt";
  int V = 8;
  cout << fixed << setprecision(2);

  // Test Weighted Dense Graph
  DenseGraph<double> g1 = DenseGraph<double>(V, false);
  ReadGraph<DenseGraph<double>, double> readGraph1(g1, filename);
  g1.show();
  cout << endl;

  // Test Weighted Sparse Graph
  SparseGraph<double> g2 = SparseGraph<double>(V, false);
  ReadGraph<SparseGraph<double>, double> readGraph2(g2, filename);
  g2.show();
  cout << endl;

  // Test Lazy Prim MST
  cout << "Test Lazy Prim MST:" << endl;
  LazyPrimMST<SparseGraph<double>, double> lazyPrimMST(g2);
  vector<Edge<double> > mst = lazyPrimMST.mstEdges();
  for (int i = 0; i < mst.size(); i++)
    cout << mst[i] << endl;
  cout << "The MST weight is: " << lazyPrimMST.result() << endl;


  KruskalMST<SparseGraph<double>, double> kruskal_mst(g2);
  vector<Edge<double> > mst1 = kruskal_mst.mstEdges();
  for (int i = 0; i < mst1.size(); i++)
    cout << mst1[i] << endl;
  cout << "The MST weight is: " << kruskal_mst.result() << endl;

  cout << endl;
  return 0;
}