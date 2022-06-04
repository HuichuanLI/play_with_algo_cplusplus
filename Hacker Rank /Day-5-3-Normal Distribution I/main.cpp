//
// Created by 李汇川 on 2022/5/29.
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int fact(int n)
{
  if(n < 2)
    return 1;
  return n*fact(n-1);
}
int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */

  double prob = ((pow(2.5, 5))*(pow(2.71, (-2.5))))/fact(5);

  printf("%0.3f", prob);

  return 0;
}