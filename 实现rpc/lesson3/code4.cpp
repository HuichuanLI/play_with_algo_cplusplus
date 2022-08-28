//
// Created by lhc456 on 2022/8/16.
//
#include <iostream>
#include <functional>

void test1() { std::cout << "function" << std::endl; }

int test2(int i) { return i; }

int test3(int i, int j) { return i + j; }

struct A {
    void foo(int i) { std::cout << i << std::endl; }
};

int main() {
    std::function<void()> fn1 = std::bind(test1);
    std::function<int(int)> fn2 = std::bind(test2, std::placeholders::_1);
    std::function<int(int, int)> fn3 = std::bind(test3, std::placeholders::_1, std::placeholders::_2);
    std::function<int(int)> fn4 = std::bind(test3, 3, std::placeholders::_1);
    std::function<int()> fn5 = std::bind(test3, 3, 4);

    A a;
    std::function<void(int)> fn6 = std::bind(&A::foo, &a, std::placeholders::_1);

    fn1();
    std::cout << fn2(1) << std::endl;
    std::cout << fn3(2, 3) << std::endl;
    std::cout << fn4(3) << std::endl;
    std::cout << fn5() << std::endl;
    fn6(8);
}