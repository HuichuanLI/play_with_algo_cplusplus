//
// Created by 李汇川 on 2022/3/19.
//

#ifndef DYNAMIC_ARRAY_STACK_ARRAYSTACK_H_
#define DYNAMIC_ARRAY_STACK_ARRAYSTACK_H_
#include "Array.h"
#include "Stack.h"
template<typename T>
class ArrayStack : public Stack<T> {
 public:
  ArrayStack(int capacity) {
    array = new Array<T>(capacity);
  }

  ArrayStack() {
    array = new Array<T>();
  }

  ~ArrayStack() {
    delete[] array;
    array = nullptr;
  }

  int getSize() {
    return array->getSize();
  }

  T pop() {
    return array->removeLast();
  }

  T peek() {
    return array->getLast();
  }

  void push(T e) {
    array->addLast(e);
  }

  bool isEmpty() {
    return array->isEmpty();
  }

  /**
   * 打印数组的所有元素
   */
  void print() {
    std::cout << "ArrayStack: size = " << array->getSize() << ", capacity = " << array->getCapacity() << std::endl;
    std::cout << "bottom ";
    array->print();
    std::cout << " top" << std::endl;
  }

 private:
  Array<T> *array;
};

#endif //DYNAMIC_ARRAY_STACK_ARRAYSTACK_H_
