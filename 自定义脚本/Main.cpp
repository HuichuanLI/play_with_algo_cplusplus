#include <string.h>
#include <iostream>
#include "Interpreter.h"
#include "Utils.hpp"

int main() {
//    if (argc < 2) {
//        panic("Feed your *.nyx source file to interpreter!\n");
//    }

//    Interpreter nyx(argv[1]);
//    nyx.execute();
    Parser::printLex("/Users/lhc456/Desktop/c++/play_with_algo_cplusplus/自定义脚本/helloworld.nyx");
    return 0;
}
