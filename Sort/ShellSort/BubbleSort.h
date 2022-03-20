//
// Created by 李汇川 on 2022/3/13.
//

#ifndef PLAY_WITH_ALGO_SHELLSORT_BUBBLESORT_H_
#define PLAY_WITH_ALGO_SHELLSORT_BUBBLESORT_H_

// 我们的第二版bubbleSort,使用newn进行优化
template<typename T>
void bubbleSort(T arr[], int n) {

  int newn; // 使用newn进行优化

  do {
    newn = 0;
    for (int i = 1; i < n; i++)
      if (arr[i - 1] > arr[i]) {
        swap(arr[i - 1], arr[i]);

        // 记录最后一次的交换位置,在此之后的元素在下一轮扫描中均不考虑
        newn = i;
      }
    n = newn;
  } while (newn > 0);
}

#endif //PLAY_WITH_ALGO_SHELLSORT_BUBBLESORT_H_
