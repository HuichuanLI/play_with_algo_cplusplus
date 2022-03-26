//
// Created by 李汇川 on 2022/3/26.
//


// main.cpp

#include <iostream>

#include "rtti.h"

using namespace rttilib;
using namespace std;

// 定义好下面用于测试库的对象及其复杂的继承关系
class A : public rttiport<A> {};
class B : public rttiport<B> {};
class C : public rttiport<C> {};
class D : public rttiport<D> {};
class E : public rttiport<E> {};
class AB : public virtual A, public virtual B, public rttiport<AB> {};
class CD : public virtual C, public virtual D, public rttiport<CD> {};
class AB_CD : public virtual AB, public virtual CD, public rttiport<AB_CD> {};
class AB_CD_E : public virtual AB, public virtual CD, public virtual E, public rttiport<AB_CD_E> {};
#include <memory>
#include <ctime>
#include <vector>

void test_speed() {
  std::time_t rttilib_t = 0;
  std::time_t dyncast_t = 0;
  const int times = 10;
  const int size = 80000;

  for (int a = 0; a < times; a++) {
    std::vector<std::shared_ptr<A>> vec;
    for (int i = 0; i < size; i++)
      vec.push_back(std::make_shared<AB_CD_E>());
    std::time_t t = clock();
    for (int i = 0; i < size; i++)
      rttilib::cast<AB_CD_E>(vec[i].get());
    rttilib_t += clock() - t;

    t = clock();
    for (int i = 0; i < size; i++)
      dynamic_cast<AB_CD_E *>(vec[i].get());
    dyncast_t += clock() - t;
    vec.clear();
  }
  std::cout << "avg time of rtti_library: " << rttilib_t / times << std::endl;
  std::cout << "avg time of dynamic_cast: " << dyncast_t / times << std::endl;
}

void test_useage() {
  std::cout.setf(std::ios::boolalpha);

  // 定义对象 AB_CD_E, 该对象继承自 AB,CD,E, 其中 AB 和 CD 分别继承自 A,B 和 C,D
  AB_CD_E *obj1 = new AB_CD_E();

  // 使用 `isKindOf` 方法来判断 AB_CD_E 对象是否是 A 类型的对象, true
  cout << "Is object of A type? " << obj1->isKindOf(rttiport<A>::type()) << endl;
  // 提供的另一种使用方法 rttilib::is
  cout << "Is object of A type? " << rttilib::is<A>(obj1) << endl;
  // 判断 AB_CD_E 对象是否是 E 类型的对象, true
  cout << "Is object of E type? " << obj1->isKindOf(rttiport<E>::type()) << endl;
  // 提供的另一种使用方法 rttilib::is
  cout << "Is object of E type? " << rttilib::is<E>(obj1) << endl;
  delete obj1;
  cout << endl;

  A *obj2 = new AB_CD_E();
  // 判断 A 类指针指向的 AB_CD_E 对象是否是 A 类型的对象, true
  cout << "Is object of A type? " << obj2->isKindOf(rttiport<A>::type()) << endl;
  // 判断 A 类指针指向的 AB_CD_E 对象是否是 E 类型的对象, true
  cout << "Is object of E type? " << obj2->isKindOf(rttiport<E>::type()) << endl;
  delete obj2;
  cout << endl;

  AB *obj3 = new AB();
  // 判断 AB 类指针指向的 AB 对象是否是 A 类型的对象, true
  cout << "Is object of A type? " << obj3->isKindOf(rttiport<A>::type()) << endl;
  // 判断 AB 类指针指向的 AB 对象是否是 E 类型的对象, true
  cout << "Is object of E type? " << obj3->isKindOf(rttiport<E>::type()) << endl;
  delete obj3;
  cout << endl;

  CD *obj4 = new CD();
  // 判断 CD 类指针指向的 CD 对象是否是 A 类型的对象, true
  cout << "Is object of A type? " << obj4->isKindOf(rttiport<A>::type()) << endl;
  // 判断 CD 类指针指向的 CD 对象是否是 E 类型的对象, true
  cout << "Is object of E type? " << obj4->isKindOf(rttiport<E>::type()) << endl;
  delete obj4;
  cout << endl;
}

int main(int argc, char *argv[]) {
  test_speed();
  test_useage();
  return 0;
}