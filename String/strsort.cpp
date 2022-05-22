//
// Created by 李汇川 on 2022/5/22.
//
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string minNumber(vector<int> &nums);
bool compare(const string &a, const string &b);

int main() {
  vector<int> nums;
  nums.push_back(3);
  nums.push_back(32);
  nums.push_back(321);
  cout << minNumber(nums) << endl;

  return 0;
}

string minNumber(vector<int> &nums) {
  vector<string> strs;
  string res;
  for (auto num: nums) {
    strs.push_back(to_string(num));
  }
  // 排序
  sort(strs.begin(), strs.end(), compare);
  for (auto str: strs) {
    res += str;
  }
  return res;
}
bool compare(const string &a, const string &b) {
  return a + b < b + a;
}