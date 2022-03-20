//
// Created by 李汇川 on 2022/3/19.
//

#include <iostream>
#include "ST.h"

int main() {
  int nums[] = {-2, 0, 3, -5, 2, -1};

  ST<int> *st = new ST<int>(nums, sizeof(nums) / sizeof(int), [](int a, int b) -> int {
    return max(a, b);
  });
  std::cout << st->query(0, 1) << std::endl;

  st = new ST<int>(nums, sizeof(nums) / sizeof(int), [](int a, int b) -> int {
    return min(a, b);
  });
  std::cout << st->query(1, 4) << std::endl;
  return 0;
}