//
// Created by 李汇川 on 2022/5/22.
//
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isContain(string &sources, string &patterns);

int main() {
  vector<int> nums;
  string source = "ABACDABABC";
  string pattern = "BAB";
  cout << isContain(source, pattern) << endl;

  return 0;
}

bool isContain(string &sources, string &patterns) {
  int i = 0;
  int j = 0;
  while (i < sources.size() && j < patterns.size()) {
    if (sources[i] == patterns[j]) {
      i += 1;
      j += 1;
    } else {
      i = i - j + 1;
      j = 0;
    }
  }
  if (j == patterns.size()) {
    return true;
  } else {
    return false;
  }
}