//
// Created by 李汇川 on 2022/5/22.
//
#include<iostream>
#include<queue>
using namespace std;
class Node {
 public:
  int x;
  int y;

  Node(int x, int y) {
    this->x = x;
    this->y = y;
  }

};
class BFS {
 public:
  int width, height;
  char **maps;
  bool **visited;
  // 上 左 下 右
  int directors[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
  int **results;
  queue<Node> queue;

  BFS(int width, int height, char **maps) {
    this->width = width;
    this->height = height;
    visited = new bool *[height];
    for (int i = 0; i < height; i++) {
      visited[i] = new bool[width];
      for (int j = 0; j < width; j++) {
        visited[i][j] = false;
      }
    }
    results = new int *[height];
    for (int i = 0; i < height; i++) {
      results[i] = new int[width];
      for (int j = 0; j < width; j++) {
        results[i][j] = 0;
      }
    }
    this->maps = maps;
  }

  int bfs(int x, int y) {
    // 初始化加入头结点
    queue.push(Node(x, y));
    visited[x][y] = true;
    results[x][y] = 0;

    // 循环判断队列是否为空
    while (!queue.empty()) {
      // 弹出头结点
      Node currentNode = queue.front();
      queue.pop();
      // 当前的 x，y 坐标
      int currentX = currentNode.x;
      int currentY = currentNode.y;
      // 遍历四个方向
      for (int i = 0; i < 4; i++) {
        // 下一个坐标
        int nextX = currentX + directors[i][0];
        int nextY = currentY + directors[i][1];
        // 判断不是 * 且合法，且没有访问过
        if (
            nextX >= 0 &&
                nextX < width &&
                nextY >= 0 &&
                nextY < height &&
                maps[nextX][nextY] != '*' &&
                !visited[nextX][nextY]
            ) {
          // 如果是出口
          if (maps[nextX][nextY] == 'T') {
            // 直接 +1 返回
            return results[currentX][currentY] + 1;
          } else {
            // 置为访问过
            visited[nextX][nextY] = true;
            // 路程 +1
            results[nextX][nextY] = results[currentX][currentY] + 1;
            // 添加到队列
            queue.push(Node(nextX, nextY));
          }
        }
      }
    }
    return -1;
  }
};
int main() {
  char *maps[] = {"*S*#", "###*", "**#*", "*##*", "T#**"};
  BFS bfs = BFS(5, 5, maps);
  cout << "最终步数：" << bfs.bfs(0, 1) << endl;
  return 0;
}