//
//  main.cpp
//  LeakDetector


#include <iostream>
#include "LeakDetector.hpp"

// 测试异常分支泄露
class Err {
public:
    Err(int n) {
        if(n == 0) throw 1000;
        data = new int[n];
    }
    ~Err() {
        delete[] data;
    }
private:
    int *data;
};

int main() {
    
    // 忘记释放指针 b 申请的内存，从而导致内存泄露
    int *a = new int;
    int *b = new int[12];
    
    delete a;
    
    // 0 作为参数传递给构造函数将发生异常，从而导致异常分支的内存泄露
    try {
        Err* e = new Err(0);
        delete e;
    } catch (int &ex) {
        std::cout << "异常错误: " << ex << std::endl;
    };

    
    return 0;
    
}
