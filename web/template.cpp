//
// Created by lhc456 on 2022/8/13.
//
#include <iostream>

using namespace std;

// 一个函数适用于多种数据类型.
template<typename myType>
myType myMax(myType x, myType y) {
    return (x > y) ? x : y;
}

int main() {
    cout << myMax<int>(3, 7) << endl; // 调用 int 类型的 myMax() 函数
    cout << myMax<double>(3.0, 7.0) << endl; // 调用 double 类型的 myMax() 函数
    cout << myMax<char>('g', 'e') << endl; // 调用 char 类型的 myMax() 函数
    return 0;
}