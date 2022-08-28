//
// Created by lhc456 on 2022/8/16.
//
#include <iostream>
#include <functional>

class person {
public:
    person(const std::function<void(int)> &f) : callback_(f) {}

    void set_age(int age) {
        age_ = age;
        if (callback_) {
            callback_(age);
        }
    }

private:
    std::function<void(int)> callback_;
    int age_ = 20;
};


void update(int person_age) {
    std::cout << "update person age: " << person_age << std::endl;
}


int main() {
    std::function<void(int)> callback = std::bind(update, std::placeholders::_1);

    person p(callback);
    p.set_age(30);
}