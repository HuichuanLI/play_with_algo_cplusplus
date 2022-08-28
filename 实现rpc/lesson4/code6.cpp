//
// Created by lhc456 on 2022/8/16.
//
#include <iostream>
#include <functional>
#include <thread>
#include <memory>
#include <atomic>

class counter {
public:
    counter() : counter_(0) {};

    void increase() {
        counter_++;
    }

    void print_counter() {
        std::cout << "thread id: " << std::this_thread::get_id() << " counter: " << counter_ << std::endl;
    }

private:
    std::atomic<int> counter_;
};

int main() {
    counter ct;

    std::thread thd1([&ct] {
        ct.increase();
    });

    std::thread thd2([&ct] {
        ct.increase();
    });

    std::thread thd3([&ct] {
        ct.print_counter();
    });

    thd1.join();
    thd2.join();
    thd3.join();
}