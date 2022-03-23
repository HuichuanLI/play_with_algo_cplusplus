//
// Created by 李汇川 on 2022/3/23.
//

#ifndef PLAY_WITH_ALGO_SMARTPOINTER_SMARTPOINTV2_SMARTPOINTER_H_
#define PLAY_WITH_ALGO_SMARTPOINTER_SMARTPOINTV2_SMARTPOINTER_H_
template<typename T>  // 将智能指针类定义成模板类
class SmartPointer {
 public:
  // 默认构造函数
  SmartPointer() : mPointer(NULL) { std::cout << "Create null smart pointer." << std::endl; }
  // 接收不同指针类型的构造函数
  SmartPointer(T *p) : mPointer(p) {
    std::cout << "Create smart pointer at " << static_cast<const void *>(p) << std::endl;
  }
  // 析构函数
  ~SmartPointer() {
    std::cout << "Release smart pointer at " << static_cast<const void *>(mPointer) << std::endl;
    // 实现内存资源自动销毁机制
    if (mPointer) delete mPointer;
  }
  // 拷贝构造函数
  SmartPointer(const SmartPointer &other) : mPointer(other.mPointer) {
    std::cout << "Copy smart pointer at " << static_cast<const void *>(other.mPointer) << std::endl;
  }
  // 赋值操作符
  SmartPointer &operator=(const SmartPointer &other) {
    // 处理自我赋值的情况
    if (this == &other) return *this;
    // 处理底层指针的释放问题
    if (mPointer) delete mPointer;
    mPointer = other.mPointer;
    std::cout << "Assign smart pointer at " << static_cast<const void *>(other.mPointer) << std::endl;
    return *this;
  }

 private:
  T *mPointer; // 指向智能指针实际对应的内存资源，根据参数自动推导规则，定义内部资源指针类型
};
#endif //PLAY_WITH_ALGO_SMARTPOINTER_SMARTPOINTV2_SMARTPOINTER_H_
