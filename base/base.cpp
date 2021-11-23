//
// Created by 李汇川 on 2021/11/23.
//

#include "base.h"
#include <iostream>

void sign_unsign() {
  int i = -10;
  unsigned int u = 5;

  int a1 = i + u;
  unsigned int a2 = i + u;

  std::cout << i + u << std::endl;
  std::cout << a2 << std::endl;

  if (u > i) {
    std::cout << "Alice" << std::endl;
  } else {
    std::cout << "Bob" << std::endl;
  }
}

int main(){

}