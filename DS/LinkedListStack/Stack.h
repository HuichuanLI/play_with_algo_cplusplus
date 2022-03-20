//
// Created by 李汇川 on 2022/3/19.
//

#ifndef DYNAMIC_ARRAY_STACK_STACK_H_
#define DYNAMIC_ARRAY_STACK_STACK_H_
template<typename T>
class Stack {
 public:
  virtual int getSize() = 0;

  virtual bool isEmpty() = 0;

  virtual void push(T e) = 0;

  virtual T pop() = 0;

  virtual T peek() = 0;
};

#endif //DYNAMIC_ARRAY_STACK_STACK_H_
