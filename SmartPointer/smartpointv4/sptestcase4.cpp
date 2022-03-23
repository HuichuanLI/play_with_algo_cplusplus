/*
* file name : sptestcase4.cpp
* desp : 智能指针测试代码 case4 测试智能指针的解引用、判空及比较功能
*/

#include <iostream>
#include "smartpointer.h"

/*继承于引用计数基类的SomeClass类*/
class SomeClass : public RefBase {
 public:
  SomeClass() { std::cout << "SomeClass default constructor !" << std::endl; }
  ~SomeClass() { std::cout << "SomeClass deconstructor !" << std::endl; }
  void func() { std::cout << "SomeClass func()" << std::endl; }
};

/*继承于引用计数基类的OtherClass类*/
class OtherClass : public RefBase {
 public:
  OtherClass() { std::cout << "OtherClass default constructor !" << std::endl; }
  ~OtherClass() { std::cout << "OtherClass deconstructor !" << std::endl; }
  void foo() { std::cout << "OtherClass foo()" << std::endl; }
};

// 解引用测试
void testcase4_1(void) {
  std::cout << "=======testcase4_1=========" << std::endl;
  SmartPointer<SomeClass> spsomeclass = new SomeClass();
  (*spsomeclass).func();
  spsomeclass->func();
  std::cout << "==========================" << std::endl;
}

// 判空与比较测试
void testcase4_2(void) {
  std::cout << "=======testcase4_2=========" << std::endl;
  SomeClass *psomeclass = new SomeClass();
  SmartPointer<SomeClass> spsomeclass = psomeclass;

  SmartPointer<OtherClass> spotherclass = new OtherClass();
  SmartPointer<OtherClass> spotherclass2 = spotherclass;

  if (spsomeclass == NULL) std::cout << "spsomeclass is NULL pointer" << std::endl;
  if (spotherclass != NULL) std::cout << "spotherclass is not NULL pointer" << std::endl;
  if (spsomeclass == psomeclass)
    std::cout << "spsomeclass and psomeclass are same pointer" << std::endl;
  if (spsomeclass != psomeclass)
    std::cout << "spsomeclass and psomeclass are not same pointer" << std::endl;
//     if (spsomeclass != spotherclass) // ERROR !
//        std::cout<< "spsomeclass and spotherclass are not same pointer" << std::endl;
//     if (spsomeclass == spotherclass) // ERROR !
//        std::cout<< "spsomeclass and spotherclass are same pointer" << std::endl;
  if (spotherclass == spotherclass2) std::cout << "spotherclass and spotherclass2 are same pointer" << std::endl;
  if (spotherclass != spotherclass2) std::cout << "spotherclass and spotherclass2 are not same pointer" << std::endl;
  std::cout << "==========================" << std::endl;

}

int main(void) {
  testcase4_1();
  testcase4_2();
  return 0;
}