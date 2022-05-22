//
// Created by 李汇川 on 2022/5/22.
//
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int *maxSlidingWindow(int nums[], int n, int k);
int main() {
  int nums[8] = {3, 5, -1, 3, 2, 5, 1, 6};
  int size = sizeof(nums) / sizeof(nums[0]);
  int *result = maxSlidingWindow(nums, size, 3);
  for (int i = 0; i < (size - 3 + 1); i++) {
    cout << result[i] << " ";
  }
  cout << endl;
  return 0;
}

int *maxSlidingWindow(const vector<int> &nums, unsigned int k) {
  if (nums.size() <= 0 || k <= 0) {
    return new int[0];
  }
  int len = nums.size();
  int *results = new int[len - k + 1]();
  // 双向队列
  deque<int> queue;
  for (int i = 0; i < len; i++) {
    // 移除比较小的元素
    while (!queue.empty() && nums[queue.back()] < nums[i]) {
      queue.pop_back();
    }
    // 添加当前元素
    queue.push_back(i);
    // 移除索引不在有效窗口内的元素
    if (i - queue.front() >= k) {
      queue.pop_front();
    }
    // 计算窗口内的数据
    if (i >= k - 1) {
      results[i - k + 1] = nums[queue.front()];
    }
  }
  return results;
}