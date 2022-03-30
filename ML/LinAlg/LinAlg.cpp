//
// Created by 李汇川 on 2022/3/30.
//

#include "LinAlg.h"
#include "Stat/Stat.hpp"
#include <iostream>
#include <random>
#include <map>
#include <cmath>

namespace LinAlg {

double LinAlg::norm_sq(std::vector<double> a) {
  double n_sq = 0;
  for (int i = 0; i < a.size(); i++) {
    n_sq += a[i] * a[i];
  }
  return n_sq;
}
std::vector<std::vector<double>> LinAlg::subtraction(std::vector<std::vector<double>> A,
                                                     std::vector<std::vector<double>> B) {
  std::vector<std::vector<double>> C;
  C.resize(A.size());
  for (int i = 0; i < C.size(); i++) {
    C[i].resize(A[0].size());
  }

  for (int i = 0; i < A.size(); i++) {
    for (int j = 0; j < A[0].size(); j++) {
      C[i][j] = A[i][j] - B[i][j];
    }
  }
  return C;
}

// Multidimensional Euclidean Distance
double LinAlg::euclideanDistance(std::vector<double> a, std::vector<double> b) {
  double dist = 0;
  for (int i = 0; i < a.size(); i++) {
    dist += (a[i] - b[i]) * (a[i] - b[i]);
  }
  return std::sqrt(dist);
}

void LinAlg::printMatrix(std::vector<std::vector<double>> A) {
  for (int i = 0; i < A.size(); i++) {
    for (int j = 0; j < A[i].size(); j++) {
      std::cout << A[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void LinAlg::printVector(std::vector<double> a) {
  for (int i = 0; i < a.size(); i++) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;
}

};