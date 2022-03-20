//
// Created by 李汇川 on 2022/3/20.
//

#ifndef DYNAMIC_ARRAY_ST_ST_H_
#define DYNAMIC_ARRAY_ST_ST_H_
#include <iostream>
#include <cmath>
#include <functional>
using namespace std;

const int maxn = 10;
template<typename T>

class ST {
 public:
  ST(T *arr, int n, std::function<T(T, T)> function) {
    data = new T[n];
    this->function = function;
    for (int i = 0; i < n; ++i) {
      data[i] = arr[i];
    }

    int k = log2(n);

//    f = new T[1 << maxn][maxn];
    for (int i = 1; i <= n; i++)
      f[i][0] = arr[i - 1];
    for (int j = 1; j <= k; j++) {
      for (int i = 1; i <= n - (1 << j) + 1; i++) {
        f[i][j] = function(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
      }
    }
  }

  T query(int l, int r) {
    int k = log2(r - l + 1);
    return function(f[l][k], f[r - (1 << k) + 1][k]);

  }
 private:
  T *data;
  T f[1 << maxn][maxn];
  int size;
  std::function<T(T, T)> function;

};
#endif //DYNAMIC_ARRAY_ST_ST_H_
