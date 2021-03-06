//
// Created by 李汇川 on 2022/3/13.
//

#ifndef PLAY_WITH_ALGO_BUBBLESORT_INSERTIONSORT_H_
#define PLAY_WITH_ALGO_BUBBLESORT_INSERTIONSORT_H_

#include <iostream>
#include <algorithm>

using namespace std;


template<typename T>
void insertionSort(T arr[], int n){

  for( int i = 1 ; i < n ; i ++ ) {

    T e = arr[i];
    int j;
    for (j = i; j > 0 && arr[j-1] > e; j--)
      arr[j] = arr[j-1];
    arr[j] = e;
  }

  return;
}
#endif //PLAY_WITH_ALGO_BUBBLESORT_INSERTIONSORT_H_
