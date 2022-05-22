//
// Created by 李汇川 on 2022/5/22.
//
#include <iostream>
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

int *maxSlidingWindow(int nums[], int n, int k) {
  if (n == 0 || k == 0) {
    return new int[0];
  }
  int *results = new int[n - k + 1]();
  for (int i = 0; i < n - k + 1; i++) {
    int max = INT_MIN;
    for (int j = i; j < i + k; j++) max = std::max(max, nums[j]);
    results[i] = max;
  }
  return results;
}