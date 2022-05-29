//
// Created by 李汇川 on 2022/5/29.
//

#ifndef PLAY_WITH_ALGO_GRAPH_GRAPH_READGRAPH_H_
#define PLAY_WITH_ALGO_GRAPH_GRAPH_READGRAPH_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>
using namespace std;

// 读取图算法
template<typename Graph>
class ReadGraph {

 public:
  // 从文件filename中读取图的信息, 存储进图graph中
  ReadGraph(Graph &graph, const string &filename) {
    ifstream file(filename.c_str());
    string line;
    int V, E;

    std::cout << file.is_open() << std::endl;
    // 第一行读取图中的节点个数和边的个数
    getline(file, line);
    stringstream ss(line);
    ss >> V >> E;

//    assert(V == graph.V());

    // 读取每一条边的信息
    for (int i = 0; i < E; i++) {

      getline(file, line);
      stringstream ss(line);

      int a, b;
      ss >> a >> b;
      assert(a >= 0 && a < V);
      assert(b >= 0 && b < V);
      graph.addEdge(a, b);
    }
  }
};

#endif //PLAY_WITH_ALGO_GRAPH_GRAPH_READGRAPH_H_
