
//
// Created by 李汇川 on 2022/5/22.
//
#include<iostream>
#include <list>
using namespace std;
class Position {
 public:
  int row;
  int col;

  Position(int row, int col) {
    this->col = col;
    this->row = row;
  }
};
class Maze {
 public:
  int **maze;
  // 双向链表，可以作为队列，也可以作为堆栈
  list<Position> queue;
  bool **visited;
  // 行
  int row;
  int col;
  Maze(int row, int col) {
    this->row = row;
    this->col = col;
    maze = new int *[row];
    for (int i = 0; i < row; i++) {
      maze[i] = new int[col];
    }

    visited = new bool *[row];
    for (int i = 0; i < row; i++) {
      visited[i] = new bool[col];
    }
  }
  void findPath() {
    int i = 0;
    int j = 0;
    // 进去第一个格子
    visited[i][j] = true;
    queue.push_back(Position(i, j));
    // 堆栈不为空，而且横纵坐标都在合法的范围
    while (!queue.empty() && (!(i == (row - 1) && (j == col - 1)))) {
      // 向右边走
      if (j < col - 1 && (maze[i][j + 1] == 0) && (!visited[i][j + 1])) {
        visited[i][j + 1] = true;
        queue.push_back(Position(i, j + 1));
        j++;
      } else if (i < row - 1 && (maze[i + 1][j] == 0) && (!visited[i + 1][j])) {
        // 向下走
        visited[i + 1][j] = true;
        queue.push_back(Position(i + 1, j));
        i++;
      } else if (j > 0 && (maze[i][j - 1] == 0) && (!visited[i][j - 1])) {
        // 向左边走
        visited[i][j - 1] = true;
        queue.push_back(Position(i, j - 1));
        j--;
      } else if (i > 0 && (maze[i - 1][j] == 0) && (!visited[i - 1][j])) {
        // 向上走
        visited[i - 1][j] = true;
        queue.push_back(Position(i - 1, j));
        i--;
      } else {
        queue.pop_back();
        if (queue.empty()) {
          break;
        }
        i = queue.back().row;
        j = queue.back().col;
      }
    }

    if (queue.empty()) {
      cout << "没有路径" << endl;
    } else {
      cout << "路径如下：" << endl;
      while (!queue.empty()) {
        Position p1 = queue.front();
        queue.pop_front();
        maze[p1.row][p1.col] = -1;
      }
      for (int k = 0; k < row; ++k) {
        for (int t = 0; t < col; ++t) {
          if (maze[k][t] == -1) {
            cout << "# ";
          } else {
            cout << maze[k][t] << " ";
          }
        }
        cout << endl;
      }
    }
  }
};

int main() {
  int row, col;
  cout << "请输入迷宫的行数：" << endl;

  cin >> row;
  cout << "请输入迷宫的列数：" << endl;
  cin >> col;
  Maze maze = Maze(5, 5);
  cout << "请输入" << row << "行" << col << "列的迷宫：" << endl;
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      cin >> maze.maze[i][j];
      maze.visited[i][j] = false;
    }
  }
  maze.findPath();
  return 0;
}