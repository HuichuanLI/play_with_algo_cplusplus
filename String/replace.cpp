//
// Created by 李汇川 on 2022/5/22.
//
#include <iostream>
#include <string>
using namespace std;

string replaceSpace(string s);
int main() {
  string str;
  getline(cin, str);
  cout << replaceSpace(str) << endl;
  return 0;
}

string replaceSpace(string s) {
  int len = s.length();
  string str = "";
  int sum = 0;
  for (int i = 0; i < len; i++) {
    if (s[i] == ' ') {
      sum++;
    }
  }
  int k = len + sum * 3 + 1;
  char *sc = new char(k);
  sc[k - 1] = '\0';
  k = 0;
  for (int i = 0; i < len; i++) {
    if (s[i] == ' ') {
      sc[k++] = 'C';
      sc[k++] = 'O';
      sc[k++] = 'D';
      sc[k++] = 'E';
    } else {
      sc[k++] = s[i];
    }
  }
  return sc;
}