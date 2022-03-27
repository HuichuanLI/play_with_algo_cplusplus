//
// Created by 李汇川 on 2022/3/27.
//

#ifndef DYNAMIC_ARRAY_DS_SET_MAP_SET_H_
#define DYNAMIC_ARRAY_DS_SET_MAP_SET_H_

template<typename T>
class Set {
  virtual void add(T e) = 0;

  virtual void remove(T e) = 0;

  virtual bool contains(T e) = 0;

  virtual int getSize() = 0;

  virtual bool isEmpty() = 0;
};

#endif //DYNAMIC_ARRAY_DS_SET_MAP_SET_H_
