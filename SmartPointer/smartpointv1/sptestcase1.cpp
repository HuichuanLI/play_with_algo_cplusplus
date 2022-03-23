//
// Created by 李汇川 on 2022/3/23.
//

/*
* file name : sptestcase1.cpp
* desp : 智能指针测试代码 case1 测试智能指针的创建与销毁
*/

#include <iostream>
#include "smartpointer.h"
class SomeClass{
 public:
  SomeClass(){std::cout << "SomeClass default constructor !"<<std::endl;}
};

void testcase1()
{
  // 创建一个不知所指的智能指针
  SmartPointer<char> spunknown;
  // 创建空智能指针
  SmartPointer<char> spnull = NULL;
  // 创建指向具体类的智能指针
  SmartPointer<SomeClass> spclass = new SomeClass;
  // 创建字符串的智能指针
  SmartPointer<const char> spstr = "Hello world!";
}

int main(void)
{
  testcase1();
  return 0;
}