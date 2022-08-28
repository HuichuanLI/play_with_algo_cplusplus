//
// Created by lhc456 on 2022/8/16.
//
#include <iostream>
#include <memory>
#include <functional>

struct A {
    ~A() {
        std::cout << "destruct A" << std::endl;
    }
};

int main() {

    std::unique_ptr<int> p(new int(1));
    std::cout << *p << std::endl;

    {
        std::unique_ptr<A> p(new A);
        std::unique_ptr<A> p1 = std::move(p);
    }

    {
        std::unique_ptr<A[]> p(new A[3]);
    }

    {
        std::unique_ptr<A, std::function<void(A *)>> p(new A, [](A *ptr) {
            std::cout << "delete from a custom deleter...\n";
            delete ptr;
        });
    }
}