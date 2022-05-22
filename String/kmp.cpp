//
// Created by 李汇川 on 2022/5/22.
//
#include <iostream>
#include <string>
using namespace std;

void getNext(int next[], string &patterns);
int kmp(string &A, string &B);
bool isMatch(string &strA, string &strB);
int main() {
  string str1 = "12345";
  string str2 = "23451";
  cout << isMatch(str1, str2) << endl;
  return 0;
}

int kmp(string &A, string &B) {
  // next 数组，保存已匹配的字符串的最长公共前后缀(C++代码需要初始化为0)
  int next[(int) B.size()];
  for (int i = 0; i < B.size(); i++) {
    next[i] = 0;
  }

  getNext(next, B);

  int i = 0;
  int j = 0;
  while (i < (int) A.length() && j < (int) B.length()) {
    if (j == -1 || A[i] == B[j]) {
      i++;
      j++;
    } else {
      // 模式串上的指针回溯到j位置
      j = next[j];
    }
  }
  if (j == B.size()) return (i - j); else return -1;
}

bool isMatch(string &strA, string &strB) {
  int lenOfA = strA.length();
  int lenOfB = strB.length();
  if (lenOfA != lenOfB) return false;
  // 拼接成为主串
  string bigStr = strA.append(strA);
  // 判断主串中是否包含模式串
  if (kmp(bigStr, strB) != -1) {
    return true;

  } else {
    return false;
  }
}

void getNext(int next[], string &patterns) {
  int j = 0, k = -1;
  next[0] = -1;
  while (j < patterns.size() - 1) {
    if (k == -1 || patterns[j] == patterns[k]) {
      j++;
      k++;
      next[j] = k;
    } else
      k = next[k];
  }
}