//
// Created by 李汇川 on 2022/6/4.
//

#include<iostream>
#include<vector>
using namespace std;
#define N 7
int moneys[N] = {100, 50, 20, 10, 5, 2, 1};

vector<int> exchange(int n) {
  int nums[N];
  for (int i = 0; i < N; i++) {
    nums[i] = 0;
  }

  for (int i = 0; i < N; i++) {
    // 优先替换大面额
    while (n >= moneys[i]) {
      // 最多换的张数
      nums[i] = n / moneys[i];
      // 剩余的钱
      n = n - moneys[i] * nums[i];
    }
  }

  vector<int> results(nums, nums + N);
  return results;
}

int main() {
  vector<int> results = exchange(64);
  for (int i = 0; i < N; i++) {
    // 张数大于 0 才打印
    if (results[i] != 0) {
      cout << "面值 " << moneys[i] << ": " << results[i] << " 张" << endl;
    }
  }
  return 0;
}