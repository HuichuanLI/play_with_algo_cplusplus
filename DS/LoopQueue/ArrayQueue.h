//
// Created by 李汇川 on 2022/3/19.
//

#ifndef DYNAMIC_ARRAY_LOOPQUEUE_ARRAYQUEUE_H_
#define DYNAMIC_ARRAY_LOOPQUEUE_ARRAYQUEUE_H_
#include "Queue.h"
#include "Array.h"

template<typename T>
class ArrayQueue : public Queue<T> {
 public:
  ArrayQueue() {
    array = new Array<T>(10);
  }

  ArrayQueue(int capacity) {
    array = new Array<T>(capacity);
  }

  ~ArrayQueue() {
    delete[] array;
    array = nullptr;
  }

  int getSize() {
    return array->getSize();
  }

  T dequeue() {
    return array->removeFirst();
  }

  T getFront() {
    return array->getFirst();
  }

  void enqueue(T e) {
    array->addLast(e);
  }

  bool isEmpty() {
    return array->isEmpty();
  }

  /**
   * 打印数组的所有元素
   */
  void print() {
    std::cout << "ArrayQueue: size = " << array->getSize() << ", capacity = " << array->getCapacity() << std::endl;
    std::cout << "front ";
    array->print();
    std::cout << " tail" << std::endl;
  }

 private:
  Array<T> *array;
};
#endif //DYNAMIC_ARRAY_LOOPQUEUE_ARRAYQUEUE_H_
