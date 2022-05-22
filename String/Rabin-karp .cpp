//
// Created by 李汇川 on 2022/5/22.
//
#include <iostream>
#include <string>
using namespace std;

long long hashCount(string &str);
bool isMatch(string &pattern, string &source);
int main() {
  string str1 = "ABC";
  string str2 = "ABABDABCD";
  cout << isMatch(str1, str2) << endl;
  return 0;
}

long long hashCount(string &str) {
  long long hash = 0;
  for (int i = 0; i != str.length(); i++) {
    hash = 31 * hash + str[i];
  }
  // 防止溢出
  return hash % LONG_MAX;
}

bool isMatch(string &pattern, string &source) {
  // 计算模式串的 hash 值
  long long hashValue = hashCount(pattern);
  int pLen = pattern.length();
  for (int i = 0; i + pLen <= (int) source.length(); i++) {
    // 计算子串的 hash 值
    string str = source.substr(i, pLen);
    long long tempHash = hashCount(str);
    if (hashValue == tempHash) {
      return true;
    }
  }
  return false;
}