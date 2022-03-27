//
// Created by 李汇川 on 2022/3/27.
//

#ifndef DYNAMIC_ARRAY_DS_SET_MAP_BSTSET_H_
#define DYNAMIC_ARRAY_DS_SET_MAP_BSTSET_H_

#include "Set.h"
#include "BST.h"

template<typename T>
class BSTSet : public Set<T> {
 public:
  BSTSet() {
    bst = new BST<T>();
  }

  int getSize() {
    return bst->getSize();
  }

  bool isEmpty() {
    return bst->isEmpty();
  }

  bool contains(T e) {
    return bst->contains(e);
  }

  void remove(T e) {
    bst->remove(e);
  }

  void add(T e) {
    bst->add(e);
  }

 private:
  BST<T> *bst;
};

#endif //DYNAMIC_ARRAY_DS_SET_MAP_BSTSET_H_
