//
// Created by 李汇川 on 2022/6/4.
//
#include <iostream>
using namespace std;
void greedy(int distances[], int distanceOnce, int numOfGasStation) {
  // 每相邻两个加油站的距离不超过 n，否则无解
  for (int i = 0; i < numOfGasStation; i++) {
    if (distances[i] > distanceOnce) {
      return;
    }
  }
  // 出发加油第一次
  int count = 1;
  cout << "第 0 个加油站加油一次" << endl;
  // 一次行驶，不能超过90
  int onceTimeDistance = 0;
  for (int i = 0; i < numOfGasStation; i++) {
    onceTimeDistance += distances[i];
    if (onceTimeDistance > distanceOnce) {
      // 上一个加油站加油次数加1
      count++;
      // 行驶距离变成上一个加油站到现在的
      onceTimeDistance = distances[i];
      cout << "第 " << i << " 个加油站加油" << endl;
    }
  }
  cout << "加油次数：" << count << " 次" << endl;

}

int main() {
  int distances[] = {30, 40, 80, 12, 78};
  int count = 5;
  int n = 90;
  greedy(distances, n, count);
  return 0;
}