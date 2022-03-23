/*
* file name : smartpointer.h
* desp : 智能指针版本v1
*/
#ifndef __SMARTPOINTER_H__
#define __SMARTPOINTER_H__

template<typename T>  // 将智能指针类定义成模板类
class SmartPointer {
 public:
  // 默认构造函数
  SmartPointer() : mPointer(NULL) { std::cout << "create unknown smart pointer." << std::endl; }
  // 接收不同指针类型的构造函数
  SmartPointer(T *p) : mPointer(p) {
    std::cout << "create smart pointer at " << static_cast<const void *>(p) << std::endl;
  }
  // 析构函数
  ~SmartPointer() {
    std::cout << "release smart pointer at " << static_cast<const void *>(mPointer) << std::endl;
    // 实现内存资源自动销毁机制
    if (mPointer) delete mPointer;
  }
 private:
  T *mPointer; // 指向智能指针实际对应的内存资源，根据参数自动推导规则，定义内部资源指针类型
};
#endif // __SMARTPOINTER_H__