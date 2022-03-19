//
// Created by 李汇川 on 2022/3/19.
//
#include <iostream>
#include "LinkedList.h"
#include "LinkedListStack.h"

int main() {
  LinkedListStack<int> *linkedListStack = new LinkedListStack<int>();
  for (int i = 0; i < 5; ++i) {
    linkedListStack->push(i);
    linkedListStack->print();
  }
  std::cout << linkedListStack->pop() << std::endl;
  linkedListStack->print();
  linkedListStack = nullptr;
  delete linkedListStack;

  return 0;
}
