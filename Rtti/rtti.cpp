//
// Created by 李汇川 on 2022/3/26.
//

#include <iostream>

struct V {
  virtual void f() {};
};
struct A : virtual V {};
struct B : virtual V {
  B(V* v, A* a) {
    // 在构造时进行转换
    dynamic_cast<B*>(v); // 明确定义的: v 的类型为 V*, V 是 B 的基类, 结果为 B*
    dynamic_cast<B*>(a); // 未定义行为: a 的类型为 A*, A 不是 B 的基类
  }
};
struct D : A, B {
  D() : B((A*)this, this) { }
};
struct Base {
  virtual ~Base() {}
};
struct Derived: Base {
  virtual void name() {}
};

int main()
{
  D d; // 派生类对象
  A& a = d;                       // upcast
  D& new_d = dynamic_cast<D&>(a); // downcast
  B& new_b = dynamic_cast<B&>(a); // sidecast


  Base* b1 = new Base;
  if(Derived* d = dynamic_cast<Derived*>(b1))
  {
    std::cout << "从 b1 到 d 的 downcast\n";
    d->name(); // 安全调用
  }

  Base* b2 = new Derived;
  if(Derived* d = dynamic_cast<Derived*>(b2))
  {
    std::cout << "从 b2 到 d 的 downcast\n";
    d->name(); // 安全调用
  }

  delete b1;
  delete b2;
}