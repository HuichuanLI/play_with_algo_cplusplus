//
// Created by 李汇川 on 2022/3/26.
//

#ifndef RTTI_h
#define RTTI_h

#include <cstdint> // std::intptr_t
#include <array>   // std::array

#if !defined(RTTI_CHAIN_MAX_SIZE)
#define RTTI_CHAIN_MAX_SIZE 32
#endif

namespace rttilib {
// rtti 类用于模拟运行时类型识别, 该类是 rttiport 模板类的基类
// 该类被设计成协议, 所以不能直接创建此类型的对象, 应该继承后使用
class rtti {
 protected:
  std::array<std::intptr_t, RTTI_CHAIN_MAX_SIZE> inherChainID;
  std::array<void *, RTTI_CHAIN_MAX_SIZE> inherChainPtr;
  int inherChainCounter;
  rtti() : inherChainCounter(-1) {
    for (auto &id: inherChainID) id = -1;
    for (auto &ptr: inherChainPtr) ptr = 0;
  }

 public:
  virtual ~rtti() {}
  // 检测示例是否为 type 所表示的类型
  // type: 对象类型的 ID, 使用 intptr_t 表示
  // return: 指向实例的 void* 指针, 若实例没有对应的 type 则返回 nullptr
  inline void *getPtrKindOf(std::intptr_t type) {
    for (int i = 0; i <= inherChainCounter; i++)
      // 当在整个 inherChainID 中查找满足时，返回其指针
      if (inherChainID[i] == type)
        return inherChainPtr[i];
    // 否则返回空
    return nullptr;
  }
  inline bool isKindOf(std::intptr_t type) {
    return getPtrKindOf(type) == nullptr ? false : true;
  }
};

template<typename T>
class rttiport : public virtual rtti {
 private:
  static std::intptr_t id;
 public:
  static std::intptr_t type();

 protected:
  rttiport() {
    // 每继承一次, ChainCounter 就增加 1
    inherChainCounter++;
    // 并在 inherChainID 中保存类型 id
    inherChainID[inherChainCounter] = type();
    inherChainPtr[inherChainCounter] = static_cast<T *>(this); //将其转换到 T*
  }
  virtual ~rttiport() {}
};
template<typename T>
std::intptr_t rttiport<T>::id(0);
template<typename T>
std::intptr_t rttiport<T>::type() {
  // 此处我们要把 id 的地址的位模式进行重新解释，所以使用 reinterpret_cast
  return reinterpret_cast<std::intptr_t>(&id);
}

// 将 to 指向对象在运行时转换为 T 类型
template<typename T>
static T *cast(rtti *to) {
  if (to == nullptr)
    return nullptr;
  return static_cast<T *>(to->getPtrKindOf(rttiport<T>::type()));
}

// 提供另一种检查 obj 指向的对象是否为 T 类型的对象
template<typename T>
static bool is(rtti *obj) {
  if (obj == nullptr)
    return false;
  return obj->getPtrKindOf(rttiport<T>::type()) != nullptr;
}
} //namespace rttilib
#endif /* RTTI_h */