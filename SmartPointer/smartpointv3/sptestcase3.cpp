/*
* file name : sptestcase3.cpp
* desp : 智能指针测试代码 case3 测试智能指针的引用计数功能
*/

#include <iostream>
#include "smartpointer.h"

/*继承于引用计数基类的SomeClass类*/
class SomeClass : public RefBase {
 public:
  SomeClass() { std::cout << "SomeClass default constructor !" << std::endl; }
  ~SomeClass() { std::cout << "SomeClass deconstructor !" << std::endl; }
};

void testcase3(void) {
  SomeClass *pSomeClass = new SomeClass(); //1
  SmartPointer<SomeClass> spOuter = pSomeClass;
  std::cout << "SomeClass Ref Count (" << pSomeClass->getRefCount() << ") outer 1." << std::endl;
  { // inner 语句块
    SmartPointer<SomeClass> spInner = spOuter;
    std::cout << "SomeClass Ref Count (" << pSomeClass->getRefCount() << ") inner." << std::endl;
  }
  std::cout << "SomeClass Ref Count (" << pSomeClass->getRefCount() << ") outer 2." << std::endl;
  // delete pSomeClass ; 不需要也不能执行delete操作!

  std::cout << "new another SomeClass class for spOuter." << std::endl;
  SmartPointer<SomeClass> spOuter2 = new SomeClass();
  spOuter = spOuter2;// 1处new出来的SomeClass将会被自动释放
}

int main(void) {
  testcase3();
  return 0;
}