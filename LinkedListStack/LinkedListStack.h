//
// Created by 李汇川 on 2022/3/19.
//

#ifndef DYNAMIC_ARRAY_LINKEDLISTSTACK_LINKEDLISTSTACK_H_
#define DYNAMIC_ARRAY_LINKEDLISTSTACK_LINKEDLISTSTACK_H_
#include "Stack.h"
#include "LinkedList.h"
template<typename T>
class LinkedListStack : public Stack<T> {
 public:
  LinkedListStack() {
    linkedlist = new LinkedList<T>();
  }
  int getSize() {
    return linkedlist->getSize();
  }
  void push(T e) {
    linkedlist->addFirst(e);
  }
  T pop() {
    return linkedlist->removeFirst();
  }

  T peek() {
    return linkedlist->getFirst();
  }

  bool isEmpty() {
    return linkedlist->isEmpty();
  }

  void print() {
    std::cout << "Stack: size = " << linkedlist->getSize() << std::endl;
    std::cout << "bottom ";
    linkedlist->toPrint();
    std::cout << " top" << std::endl;
  }
 private:
  LinkedList<T> *linkedlist;
};
#endif //DYNAMIC_ARRAY_LINKEDLISTSTACK_LINKEDLISTSTACK_H_
