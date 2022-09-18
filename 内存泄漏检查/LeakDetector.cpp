//
//  LeakDetector.cpp
//  LeakDetector
//
//  Created by changkun on 16/9/13.
//  Copyright © 2016 shiyanlou.com, all rights reserved.
//
#include <iostream>
#include <cstring>

// 在此处定义 _DEBUG_NEW_ 宏, 从而在这个实现文件中不再重载 new 运算符, 从而防止编译冲突
#define __NEW_OVERLOAD_IMPLEMENTATION__
#include "LeakDetector.hpp"

typedef struct _MemoryList {
    struct  _MemoryList *next, *prev;
    size_t 	size;       // 申请内存的大小
    bool    isArray;    // 是否申请了数组
    char    *file;      // 存储所在文件
    unsigned int line;  // 保存所在行
} _MemoryList;
static unsigned long _memory_allocated = 0;     // 保存未释放的内存大小
static _MemoryList _root = {
    &_root, &_root, // 第一个元素的前向后向指针均指向自己
    0, false,               // 其申请的内存大小为 0, 且不是数组
    NULL, 0                 // 文件指针为空, 行号为0
};

unsigned int _leak_detector::callCount = 0;

// 从 _MemoryList 头部开始分配内存
void* AllocateMemory(size_t _size, bool _array, char *_file, unsigned _line) {
    // 计算新的大小
    size_t newSize = sizeof(_MemoryList) + _size;
    
    // 由于 new 已经被重载，我们只能使用 malloc 来分配内存
    _MemoryList *newElem = (_MemoryList*)malloc(newSize);
    
    newElem->next = _root.next;
    newElem->prev = &_root;
    newElem->size = _size;
    newElem->isArray = _array;
    newElem->file = NULL;
    
    // 如果有文件信息，则保存下来
    if (_file) {
        newElem->file = (char *)malloc(strlen(_file)+1);
        strcpy(newElem->file, _file);
    }
    // 保存行号
    newElem->line = _line;
    
    // 更新列表
    _root.next->prev = newElem;
    _root.next = newElem;
    
    // 记录到未释放内存数中
    _memory_allocated += _size;
    
    // 返回申请的内存
    return (char*)newElem + sizeof(_MemoryList);
}


void  DeleteMemory(void* _ptr, bool _array) {
    // 返回 MemoryList 开始处
    _MemoryList *currentElem = (_MemoryList *)((char *)_ptr - sizeof(_MemoryList));

    if (currentElem->isArray != _array) return;

    // 更新列表
    currentElem->prev->next = currentElem->next;
    currentElem->next->prev = currentElem->prev;
    _memory_allocated -= currentElem->size;
    
    // 记得释放存放文件信息时申请的内存
    if (currentElem->file) free(currentElem->file);
    free(currentElem);
}

// 重载 new 运算符
void* operator new(size_t _size) {
    return AllocateMemory(_size, false, NULL, 0);
}
void* operator new[](size_t _size) {
    return AllocateMemory(_size, true, NULL, 0);
}
void* operator new(size_t _size, char *_file, unsigned int _line) {
    return AllocateMemory(_size, false, _file, _line);
}
void* operator new[](size_t _size, char *_file, unsigned int _line) {
    return AllocateMemory(_size, true, _file, _line);
}
// 重载 delete 运算符
void operator delete(void *_ptr) noexcept {
    DeleteMemory(_ptr, false);
}
void operator delete[](void *_ptr) noexcept {
    DeleteMemory(_ptr, true);
}

unsigned int _leak_detector::LeakDetector(void) noexcept {
    unsigned int count = 0;
    // 遍历整个列表, 如果有内存泄露，那么 _LeakRoot.next 总不是指向自己的
    _MemoryList *ptr = _root.next;
    while (ptr && ptr != &_root)
    {
        // 输出存在内存泄露的相关信息, 如泄露大小, 产生泄露的位置
        if(ptr->isArray)
            std::cout << "泄露[] ";
        else
            std::cout << "泄露   ";
        std::cout << ptr << " 大小 " << ptr->size;
        if (ptr->file)
            std::cout << " (位于 " << ptr->file << " 第 " << ptr->line << " 行)";
        else
            std::cout << " (无文件信息)";
        std::cout << std::endl;
    
        ++count;
        ptr = ptr->next;
    }

    if (count)
        std::cout << "存在" << count << "处内存泄露, 共包括 "<< _memory_allocated << " byte." << std::endl;
    return count;
}

