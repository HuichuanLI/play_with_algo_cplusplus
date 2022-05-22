//
// Created by 李汇川 on 2022/5/22.
//
#include<iostream>
#include<vector>
using namespace std;

class Solution {
 public:

  bool find(int target, vector<vector<int> > array) {
    int i, j;
    int height = array.size();
    int weight = array[0].size();
    for (i = height - 1, j = 0; i >= 0 && i < height && j >= 0 && j < weight;) {
      // 相等，直接返回
      if (array[i][j] == target) {
        return true;
      }
      // 比当前数大，往右边移动
      if (array[i][j] < target) {
        j++;
        continue;
      }
      // 比当前数小，往上边移动
      if (array[i][j] > target) {
        i--;
        continue;
      }
    }
    return false;
  }
};

int main() {
  Solution solution;
  vector<vector<int> > array = {{1, 4, 6, 28}, {2, 7, 32, 34}, {10, 11, 67, 79}};
  cout << solution.find(32, array) << endl;
  return 0;
}