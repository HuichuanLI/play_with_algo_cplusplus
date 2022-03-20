//
// Created by 李汇川 on 2022/3/13.
//
#include <iostream>
#include <algorithm>
#include "SortTestHelper.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "BubbleSort.h"
using namespace std;

// 我们的第一版bubbleSort
template<typename T>
void shellSort(T arr[], int n) {
  int h = 1;
  while (h < n / 3)
    h = h * 3 + 1;
  while (h >= 1) {
    for (int i = h; i < n; i += 1) {
      T e = arr[i];
      int j;
      for (j = i; j >= h && e < arr[j - h]; j -= h) {
        arr[j] = arr[j - h];
      }
      arr[j] = e;
    }
    h /= 3;
  }
}

int main() {

  int n = 20000;

  // 测试1 一般测试
  cout << "Test for random array, size = " << n << ", random range [0, " << n << "]" << endl;

  int *arr1 = SortTestHelper::generateRandomArray(n, 0, n);
  int *arr2 = SortTestHelper::copyIntArray(arr1, n);
  int *arr3 = SortTestHelper::copyIntArray(arr1, n);
  int *arr4 = SortTestHelper::copyIntArray(arr1, n);

  SortTestHelper::testSort("Selection Sort", selectionSort, arr1, n);
  SortTestHelper::testSort("Insertion Sort", insertionSort, arr2, n);
  SortTestHelper::testSort("Bubble Sort", bubbleSort, arr3, n);
  SortTestHelper::testSort("Shell Sort", shellSort, arr4, n);

  delete[] arr1;
  delete[] arr2;
  delete[] arr3;
  delete[] arr4;

  cout << endl;


  // 测试2 测试近乎有序的数组
  int swapTimes = 100;

  cout << "Test for nearly ordered array, size = " << n << ", swap time = " << swapTimes << endl;

  arr1 = SortTestHelper::generateNearlyOrderedArray(n, swapTimes);
  arr2 = SortTestHelper::copyIntArray(arr1, n);
  arr3 = SortTestHelper::copyIntArray(arr1, n);
  arr4 = SortTestHelper::copyIntArray(arr1, n);

  SortTestHelper::testSort("Selection Sort", selectionSort, arr1, n);
  SortTestHelper::testSort("Insertion Sort", insertionSort, arr2, n);
  SortTestHelper::testSort("Bubble Sort", bubbleSort, arr3, n);
  SortTestHelper::testSort("Shell Sort", shellSort, arr4, n);

  delete[] arr1;
  delete[] arr2;
  delete[] arr3;
  delete[] arr4;

  return 0;
}