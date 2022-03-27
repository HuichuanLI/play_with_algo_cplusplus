//
// Created by 李汇川 on 2022/3/27.
//

#ifndef DYNAMIC_ARRAY_DS_SET_MAP_LINKEDLISTMAP_MAP_H_
#define DYNAMIC_ARRAY_DS_SET_MAP_LINKEDLISTMAP_MAP_H_

template<typename Key, typename Value>
class Map {
  void add(Key key, Value value);

  Value remove(Key key);

  bool contains(Key key);

  Value get(Key key);

  void set(Key key, Value value);

  int getSize();

  bool isEmpty();
};

#endif //DYNAMIC_ARRAY_DS_SET_MAP_LINKEDLISTMAP_MAP_H_
