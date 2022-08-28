//
// Created by lhc456 on 2022/8/16.
//
#include <iostream>
#include <functional>
#include <thread>
#include <memory>
#include <chrono>
#include <vector>

void test1() {
    std::cout << "hello test1" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void test2() {
    std::cout << "hello test2" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void test3() {
    std::cout << "hello test3" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

int main() {
    auto begin = std::chrono::high_resolution_clock::now();
    test1();
    test2();
    test3();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << std::endl;

    std::vector<std::shared_ptr<std::thread>> group;
    group.push_back(std::make_shared<std::thread>([] { test1(); }));
    group.push_back(std::make_shared<std::thread>([] { test2(); }));
    group.push_back(std::make_shared<std::thread>([] { test3(); }));

    begin = std::chrono::high_resolution_clock::now();
    for (auto &thd: group) {
        thd->join();
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << std::endl;
}