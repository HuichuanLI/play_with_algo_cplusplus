//
// Created by 李汇川 on 2022/5/29.
//
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

double phi(double x) {
  return (exp(-x * x * 0.5) / sqrt(2 * M_PI));
}

double normal(double mean, double sigma, double x) {
  return phi((x - mean) / sigma) / sigma;
}

double erf(double x) {
  int n = 100;
  double dt = x / n;
  double sum = 0;
  for (int i = 0; i < n; i++) {
    double z = i * dt + 0.5 * dt;
    sum += exp(-z * z) * dt;
  }
  return sum * 2 / sqrt(M_PI);
}

double Phi(double mean, double sigma, double x) {
  return 0.5 * (1 + erf((x - mean) / (sigma * sqrt(2))));
}

int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  double mean = 205;
  double sigma = 15;
  int n = 49;
  double mean2 = n * mean;
  double sigma2 = sqrt(n) * sigma;
  double x = 9800;
  printf("%.4f", Phi(mean2, sigma2, x));
  return 0;
}