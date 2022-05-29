#include <iostream>
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "ReadGraph.h"
#include "Components.h"
#include "Path.h"
#include "ShortestPath.h"

using namespace std;

// 测试通过文件读取图的信息
int main() {

  // 使用两种图的存储方式读取testG1.txt文件
  string filename = "/Users/hui/Desktop/c++/play_with_algo/graph/Graph/textG1.txt";
  SparseGraph g1(13, false);
  ReadGraph<SparseGraph> readGraph1(g1, filename);
  cout << "test G1 in Sparse Graph:" << endl;
  g1.show();

  cout << endl;

  DenseGraph g2(13, false);
  ReadGraph<DenseGraph> readGraph2(g2, filename);
  cout << "test G1 in Dense Graph:" << endl;
  g2.show();

  cout << endl;

  // 使用两种图的存储方式读取testG2.txt文件
  filename = "/Users/hui/Desktop/c++/play_with_algo/graph/Graph/testG2.txt";
  SparseGraph g3(6, false);
  ReadGraph<SparseGraph> readGraph3(g3, filename);
  cout << "test G2 in Sparse Graph:" << endl;
  g3.show();

  cout << endl;

  DenseGraph g4(6, false);
  ReadGraph<DenseGraph> readGraph4(g4, filename);
  cout << "test G2 in Dense Graph:" << endl;
  g4.show();

  Component<DenseGraph> component2(g2);
  cout << "TestG1.txt, Using Dense Graph, Component Count: " << component2.count() << endl;

  Path<SparseGraph> path(g1, 0);
  cout << "DFS Path from 0 to 6 : " << endl;
  path.showPath(6);

  ShortestPath<SparseGraph> bfs2(g1, 0);
  cout << "BFS : ";
  bfs2.showPath(3);
  return 0;
}