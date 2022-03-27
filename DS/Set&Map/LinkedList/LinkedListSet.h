//
// Created by 李汇川 on 2022/3/27.
//

#ifndef DYNAMIC_ARRAY_DS_SET_MAP_LINKEDLIST_LINKEDLISTSET_H_
#define DYNAMIC_ARRAY_DS_SET_MAP_LINKEDLIST_LINKEDLISTSET_H_

#include "Set.h"
#include "LinkedList.h"

template<typename T>
class LinkedListSet : public Set<T> {
 public:
  LinkedListSet() {
    list = new LinkedList<T>();
  }

  int getSize() {
    return list->getSize();
  }

  bool isEmpty() {
    return list->isEmpty();
  }

  bool contains(T e) {
    return list->contains(e);
  }

  void add(T e) {
    if (!list->contains(e)) {
      list->addFirst(e);
    }
  }

  void remove(T e) {
    list->removeElement(e);
  }

 private:
  LinkedList<T> *list;
};

#endif //DYNAMIC_ARRAY_DS_SET_MAP_LINKEDLIST_LINKEDLISTSET_H_
