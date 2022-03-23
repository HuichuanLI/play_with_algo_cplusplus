/*
* file name : smartpointer.h
* desp : 智能指针版本v3
*/
#ifndef __SMARTPOINTER_H__
#define __SMARTPOINTER_H__

template<typename T>  // 将智能指针类定义成模板类
class SmartPointer {
 public:
  // 默认构造函数
  SmartPointer() : mPointer(NULL) { std::cout << "Create null smart pointer." << std::endl; }
  // 接收不同对象类型的构造函数
  SmartPointer(T *p) : mPointer(p) {
    std::cout << "Create smart pointer at " << static_cast<const void *>(p) << std::endl;
    /*智能指针指向类T，引用计数加1*/
    if (mPointer) mPointer->incRefCount();
  }
  // 析构函数
  ~SmartPointer() {
    std::cout << "Release smart pointer at " << static_cast<const void *>(mPointer) << std::endl;
    // 实现内存资源自动销毁机制
    if (mPointer && mPointer->decRefCount() == 0) delete mPointer;
  }
  // 拷贝构造函数
  SmartPointer(const SmartPointer &other) : mPointer(other.mPointer) {
    std::cout << "Copy smart pointer at " << static_cast<const void *>(other.mPointer) << std::endl;
    // 引用计数加1
    if (mPointer) mPointer->incRefCount();
  }
  // 赋值操作符
  SmartPointer &operator=(const SmartPointer &other) {
    T *temp(other.mPointer);
    // 新指向对象，引用计数值加1
    if (temp) temp->incRefCount();
    // 原指向对象，引用计数值减1，如果减1后引用计数为0 销毁原资源对象
    if (mPointer && mPointer->decRefCount() == 0) delete mPointer;
    // 智能指针指向新资源对象
    mPointer = temp;
    return *this;
  }

 private:
  T *mPointer; // 指向智能指针实际对应的内存资源，根据参数自动推导规则，定义内部资源指针类型
};

/*引用计数基类*/
class RefBase {
 public:
  RefBase() : mCount(0) {}
  void incRefCount() {
    mCount++;
  }
  int decRefCount() {
    return --mCount;
  }
  // 调试接口，返回对象当前引用计数
  int getRefCount() {
    return mCount;
  }
  virtual ~RefBase() {}
 private:
  int mCount;
};
#endif // __SMARTPOINTER_H__