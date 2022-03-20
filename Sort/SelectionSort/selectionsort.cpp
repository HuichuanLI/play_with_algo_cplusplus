//
// Created by 李汇川 on 2022/3/13.
//

#include <iostream>
#include "SortTestHelper.h"

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

int main() {

  int n = 20000;
  int *arr = SortTestHelper::generateRandomArray(n,0,n);
  SortTestHelper::testSort("Selection Sort", selectionSort, arr, n);
  for(int i=0;i<n;i+=1)
    cout << arr[i] << " ";
  cout << endl;
  delete[] arr;

  return 0;
}