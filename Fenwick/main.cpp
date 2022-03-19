

#include <iostream>
#include "FenwickTree.h"

int main() {
  int n = 10;
  int *arr = new int[n + 1];
  for (int i = 1; i <= n; i++)
    arr[i] = i;
  FenWickTree<int> *fen_wick_tree = new FenWickTree<int>(arr, 10);

  std::cout << fen_wick_tree->sum(10) << std::endl;
  std::cout << fen_wick_tree->sum(9, 10) << std::endl;
  for (int i = 1; i <= n; i++)
    fen_wick_tree->add(i, 1);
  std::cout << fen_wick_tree->sum(10) << std::endl;
  std::cout << fen_wick_tree->sum(9, 10) << std::endl;

  return 0;
}