//
// Created by lhc456 on 2022/8/16.
//
#include <iostream>
#include <memory>

struct BigObj {
    BigObj() {
        std::cout << "big object has been constructed" << std::endl;
    }

    ~BigObj() {
        std::cout << "big object has been destructed" << std::endl;
    }
};

void test_shared_ptr() {
    BigObj *p = new BigObj();
    std::shared_ptr<BigObj> sp(p);

    std::shared_ptr<BigObj> sp1(new BigObj());
    std::shared_ptr<BigObj> sp2 = std::make_shared<BigObj>();
}

std::shared_ptr<BigObj> get_obj() {
    return std::make_shared<BigObj>();
}

int main() {

    test_shared_ptr();
    auto p = get_obj();

}