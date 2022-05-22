//
// Created by 李汇川 on 2022/5/22.
//
#include<iostream>
#include<map>
using namespace std;

class Solution {
 public:
  int *twoSum(int nums[], int size, int target) {
    // 直接返回局部变量是有问题的，需要使用static
    static int result[2];
    if (nums == NULL) {
      return result;
    }
    // 存储元素以及索引
    map<int, int> numSet;
    for (int i = 0; i < size; i++) {
      // 是否包含差值
      if (numSet.count(target - nums[i]) != 0) {
        result[0] = (int) numSet.
            find(target - nums[i])->second;
        result[1] = i;
        return result;
      } else {
        // 不包含则直接放进入 hash 表中
        numSet.insert(pair<int, int>(nums[i], i));
      }
    }
    return result;
  }

};

int main() {
  Solution solution;
  int datas[] = {5, 12, 43, 34, 6, 23};
  int size = sizeof(datas) / sizeof(datas[0]);
  int *results;
  results = solution.twoSum(datas, size, 35);
  cout << results[0] << " , " << results[1] << endl;
  return 0;
}