//
// Created by 李汇川 on 2022/5/29.
//
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

using namespace std;


vector<int> ranks(vector<double> x) {
  vector<pair<double, int>> v;

  int n = static_cast<int>(x.size());

  for (int i = 0; i < n; i++) {
    v.push_back({x[i], i});
  }

  sort(begin(v), end(v));

  vector<int> r(n);

  for (int i = 0; i < n; i++) {
    r[v[i].second] = i + 1;
  }

  return r;
}

double spearman(vector<double> x, vector<double> y) {
  vector<int> rx = ranks(x);
  vector<int> ry = ranks(y);

  int n = static_cast<int>(x.size());

  double s = 0;

  for (int i = 0; i < n; i++) {
    s += (rx[i] - ry[i]) * (rx[i] - ry[i]);
  }

  double c = (6 * s) / (n * (n * n - 1.0));

  return 1.0 - c;
}

int main() {
  int n;
  cin >> n;

  vector<double> x(n);

  for (int i = 0; i < n; i++) {
    cin >> x[i];
  }

  vector<double> y(n);

  for (int i = 0; i < n; i++) {
    cin >> y[i];
  }

  cout << setprecision(3) << fixed << spearman(x, y);

  return 0;
}