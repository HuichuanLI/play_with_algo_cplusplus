//
// Created by lhc456 on 2022/8/13.
//
#include <iostream>
#include <regex>

int main() {
    std::regex r1("S");
    printf("S works.\n");
    std::regex r2(".");
    printf(". works.\n");
    std::regex r3(".+");
    printf(".+ works.\n");
    std::regex r4("[0-9]");
    printf("[0-9] works.\n");
    return 0;
}