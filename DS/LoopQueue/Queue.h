//
// Created by 李汇川 on 2022/3/19.
//

#ifndef DYNAMIC_ARRAY_LOOPQUEUE_QUEUE_H_
#define DYNAMIC_ARRAY_LOOPQUEUE_QUEUE_H_
template<typename T>
class Queue {
 public:
  virtual int getSize() = 0;

  virtual bool isEmpty() = 0;

  virtual void enqueue(T e) = 0;

  virtual T dequeue() = 0;

  virtual T getFront() = 0;
};

#endif //DYNAMIC_ARRAY_LOOPQUEUE_QUEUE_H_
