#include<iostream>
using namespace std;

class Dijkstra {
 public:
  // 节点数
  int num;
  // 边
  int **edges;

  Dijkstra(int num, int **edges) {
    this->num = num;
    this->edges = edges;
  }

  int *dijkstra(int v) {
    if (v < 0 || v >= num) {
      return NULL;
    }
    // 最短路径是否已经找到的标识
    bool *visited = new bool[num];
    int *distance = new int[num];

    // 初始化边，如果为 0，则置为最大值
    for (int i = 0; i < num; i++) {
      for (int j = i + 1; j < num; j++) {
        // 无向图，i 到 j 和 j 到 i 一样
        if (edges[i][j] == 0) {
          edges[i][j] = INT_MAX;
          edges[j][i] = INT_MAX;
        }
      }
    }

    // copy 各个节点直接到达节点 v 的距离
    memcpy(distance, edges[v], num * sizeof(int));
    visited[v] = true;
    // 从源点到其余顶点的最短路径
    for (int i = 0; i < num; ++i) {
      int min = INT_MAX;
      int index = -1;
      // 找出到开始顶点的最短的距离
      for (int j = 0; j < num; ++j) {
        // 该顶点还没有被查找过
        if (!visited[j]) {
          // 找出路径最短的那个顶点
          if (distance[j] < min) {
            index = j;
            min = distance[j];
          }
        }
      }
      // 索引不是 -1 说明找到
      if (index != -1) {
        visited[index] = true;
      }
      cout << "找到index: " << index << " ， distance： ";
      // 更新当前最短路径及距离
      for (int x = 0; x < num; x++) {
        // 该节点还没被访问过
        if (!visited[x]) {
          /*
           * 当前顶点到 index 的距离（min）+index 到 x 的距离 < 现在的顶点到 x 的距离
           * 说明可以从顶点到 index，再到 x
           */
          if (
              edges[index][x] != INT_MAX &&
                  (min + edges[index][x] < distance[x])
              ) {
            // 更新距离
            distance[x] = min + edges[index][x];
          }
        }
      }
      // 打印
      for (int i = 0; i < num; i++) {
        cout << distance[i] << " ";
      }
      cout << endl;
    }
    return distance;
  }
};
int main() {
  int edges[6][6] = {
      {0, 0, 10, 0, 30, 100},
      {0, 0, 5, 0, 0, 0},
      {10, 5, 0, 50, 0, 0},
      {0, 0, 50, 0, 20, 10},
      {30, 0, 0, 20, 0, 60},
      {100, 0, 0, 10, 60, 0},
  };
  // 指针转换
  int *point[6];
  for (int i = 0; i < 6; i++) {
    point[i] = &edges[i][0];
  }
  Dijkstra dijkstra = Dijkstra(6, point);

  int *result = dijkstra.dijkstra(0);
  cout << "1 --> 6 最短路径：" << result[5] << endl;
  return 0;
}