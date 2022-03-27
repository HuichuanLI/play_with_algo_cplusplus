//
// Created by 李汇川 on 2022/3/27.
//

#ifndef DYNAMIC_ARRAY_DS_SET_MAP_LINKEDLISTMAP_MAP_H_
#define DYNAMIC_ARRAY_DS_SET_MAP_LINKEDLISTMAP_MAP_H_

template<typename Key, typename Value>
class Map {
  virtual void add(Key key, Value value) = 0;

  virtual Value remove(Key key) = 0;

  virtual bool contains(Key key) = 0;

  virtual Value get(Key key) = 0;

  virtual void set(Key key, Value value) = 0;

  virtual int getSize() = 0;

  virtual bool isEmpty() = 0;
};


#endif //DYNAMIC_ARRAY_DS_SET_MAP_LINKEDLISTMAP_MAP_H_
