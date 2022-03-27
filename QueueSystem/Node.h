//
// Created by 李汇川 on 2022/3/26.
//

//
//  Node.hpp
//  QueueSystem
//

#ifndef Node_hpp
#define Node_hpp

#include "Random.h"

#define RANDOM_PARAMETER 100

struct Node {
  int arrive_time;
  int duration;
  struct Node *next;

  // 默认到达事件为0，需要服务的时间是随机的
  Node(int arrive_time = 0,
       int duration = Random::getRandom(EXPONENTAIL, 0.1)) :
      arrive_time(arrive_time),
      duration(duration),
      next(NULL) {}
};

typedef struct Node Node;
typedef struct Node Customer;

#endif /* Node_h */