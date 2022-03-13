//
// Created by 李汇川 on 2022/3/13.
//

#ifndef PLAY_WITH_ALGO_INSERCTIONSORT_SELECTIONSORT_H_
#define PLAY_WITH_ALGO_INSERCTIONSORT_SELECTIONSORT_H_
#include <iostream>
#include <algorithm>

using namespace std;


template<typename T>
void selectionSort(T arr[], int n){

  for(int i = 0 ; i < n ; i ++){

    int minIndex = i;
    for( int j = i + 1 ; j < n ; j ++ )
      if( arr[j] < arr[minIndex] )
        minIndex = j;

    swap( arr[i] , arr[minIndex] );
  }
}
#endif //PLAY_WITH_ALGO_INSERCTIONSORT_SELECTIONSORT_H_
