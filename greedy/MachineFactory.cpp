//
// Created by 李汇川 on 2022/6/3.
//
#include<iostream>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int n, s;
  cin >> n >> s;
  int p, y, min_p = INT_MAX - s;
  long long total = 0;
  for (int i = 0; i < n; i++) {
    cin >> p >> y;
    min_p += s;
    if (min_p > p)
      min_p = p;
    total += min_p * y;
  }
  cout << total << endl;
  return 0;
}