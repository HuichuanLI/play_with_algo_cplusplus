//
// Created by 李汇川 on 2022/3/19.
//

#ifndef DYNAMIC_ARRAY_FENWICK_FENWICKTREE_H_
#define DYNAMIC_ARRAY_FENWICK_FENWICKTREE_H_
#include <iostream>
using namespace std;
template<typename T>

class FenWickTree {
 public:
  FenWickTree(T *arr, int n) {
    data = arr;
    size = n;
    c = new T[size + 1];
    for (int i = 1; i <= size; i++) {
      add(i, data[i]);
    }
  }

  ~FenWickTree() {
    delete[] c;
  }

  void add(int x, T k) {
    data[x] += k;
    while (x <= size) {  // 不能越界
      c[x] = c[x] + k;
      x = x + Lowbit(x);
    }
  }

  T sum(int x) {
    T sum = 0;
    while (x > 0) {
      sum += c[x];
      x -= Lowbit(x);
    }
    return sum;
  }
  T sum(int x1, int x2) { return sum(x2) - sum(x1 - 1); }

 private:
  T *data;
  T *c;
  int size;
  inline int Lowbit(int x) { return x & (-x); }

};
#endif //DYNAMIC_ARRAY_FENWICK_FENWICKTREE_H_
