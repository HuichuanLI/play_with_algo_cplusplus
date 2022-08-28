//
// Created by lhc456 on 2022/8/16.
//
#include <iostream>
#include <memory>

std::weak_ptr<int> gw;

void f() {
    if (auto spt = gw.lock()) { // 使用之前必须复制到 shared_ptr
        std::cout << *spt << "\n";
    } else {
        std::cout << "gw is expired\n";
    }
}

int main() {
    {
        auto sp = std::make_shared<int>(42);
        gw = sp;

        f();
    }

    f();
}