//
// Created by 李汇川 on 2022/5/22.
//
#include <iostream>

using namespace std;

int main() {
  string str;
  cin >> str;
  int num = 0;
  for (int i = 0; i < str.length(); i++) {
    // 转换为字符判断是否有数字
    if (str[i] >= '0' && str[i] <= '9') {
      num++;
    }
  }
  cout << num << endl;
  return 0;
}