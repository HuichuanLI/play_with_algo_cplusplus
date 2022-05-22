//
// Created by 李汇川 on 2022/5/22.
//
#include<iostream>
using namespace std;
class DFS {
 public:
  int count = 0;
  int m;
  int n;
  bool **visited;
  char **maps;
  DFS(char **maps, int m, int n) {
    this->m = m;
    this->n = n;
    visited = new bool *[m];
    for (int i = 0; i < n; i++) {
      visited[i] = new bool[count];
    }
    this->maps = maps;
  }
  void dfs() {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        // 没被访问过，并且是 #
        if (!visited[i][j] && maps[i][j] == '#') {
          // 计数 +1
          count++;
          dfs(i, j);
        }
      }
    }
  }

  void dfs(int i, int j) {
    // 非法边界
    if (i < 0 || i >= m || j < 0 || j >= n) {
      return;
    }
    // 被访问或者不是 #
    if (visited[i][j] || maps[i][j] != '#') {
      return;
    }
    visited[i][j] = true;
    // 右
    dfs(i, j + 1);
    // 左
    dfs(i, j - 1);
    // 下
    dfs(i + 1, j);
    // 上
    dfs(i - 1, j);
  }
};
int main() {
  char *maps[] = {"***##", "*##*#", "*#**#", "###*#", "##**#"};
  DFS dfs = DFS(maps, 5, 5);
  dfs.dfs();
  cout << "联通块数量： " << dfs.count << endl;
  return 0;
}