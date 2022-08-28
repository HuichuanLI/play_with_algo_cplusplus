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

void test_ref() {
    std::shared_ptr<BigObj> sp1 = std::make_shared<BigObj>();
    std::cout << sp1.use_count() << std::endl;
    std::shared_ptr<BigObj> sp2 = sp1;
    std::cout << sp2.use_count() << std::endl;
    std::shared_ptr<BigObj> sp3 = sp2;
    std::cout << sp3.use_count() << std::endl;
    std::cout << sp1.use_count() << std::endl;
}

void test_ref1() {
    std::shared_ptr<BigObj> sp1 = std::make_shared<BigObj>();
    std::cout << sp1.use_count() << std::endl;
    {
        std::shared_ptr<BigObj> sp2 = sp1;
        std::cout << sp1.use_count() << std::endl;
    }
    std::cout << sp1.use_count() << std::endl;
    BigObj *ptr = sp1.get();

    sp1 = nullptr;
    std::cout << sp1.use_count() << std::endl;
}

int main() {

    test_ref();
    test_ref1();

}