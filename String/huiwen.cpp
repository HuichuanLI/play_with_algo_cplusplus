//
// Created by 李汇川 on 2022/5/22.
//
#include <iostream>
#include <string>
using namespace std;

bool isMatch(string &s);
string longestPalindrome(string &s);

int main() {
  string str = "baca";
  cout << longestPalindrome(str) << endl;

  return 0;
}

// 判断是否是回文串
bool isMatch(string &s) {
  int len = s.size();
  for (int i = 0; i < len / 2; i++) {
    // 根据中心判断是否相等
    if (s[i] != s[len - i - 1]) {
      return false;
    }
  }
  return true;
}

string longestPalindrome(string &s) {
  string result = "";
  int maxNum = 0;
  int len = s.size();
  for (int i = 0; i < len; i++)
    for (int j = i + 1; j <= len; j++) {
      // 判断每一段子串
      string str = s.substr(i, j - i);
      if (isMatch(str) && str.size() > maxNum) {
        result = s.substr(i, j - i);
        // 记录回文串的最大长度
        maxNum = std::max(maxNum, (int) result.size());
      }
    }
  return result;
}