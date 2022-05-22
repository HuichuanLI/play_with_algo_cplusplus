//
// Created by 李汇川 on 2022/5/22.
//
#include<iostream>
#include<string>
using namespace std;

class Solution {
 public:

  int binarySearch(int datas[], int size, int target) {
    int low = 0, high = size - 1, mid;
    while (low <= high) {
      mid = low + (high - low) / 2;
      // 相等直接返回
      if (datas[mid] == target) {
        return mid;
      } else if (datas[mid] > target) {
        // 在左边一半
        high = mid - 1;
      } else {
        // 在右边一半
        low = mid + 1;
      }
    }
    return -1;
  }

};

int main() {
  Solution solution;
  int datas[] = {1, 23, 43, 56, 67, 69, 75, 81, 94};
  int size = sizeof(datas) / sizeof(datas[0]);
  int max = solution.binarySearch(datas, size, 75);
  cout <<
       "查找到 75 的索引位置为：" << max << endl;
  return 0;
}