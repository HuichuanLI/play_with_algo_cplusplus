//
// Created by 李汇川 on 2022/4/1.
//

#include "PCA.h"
#include <iostream>
#include <random>
#include "vector"
#include "../LinAlg/LinAlg.h"

namespace PCA {
PCA::PCA(std::vector<std::vector<double>> inputSet, int k) : inputSet(inputSet), k(k) {

}

std::vector<std::vector<double>> PCA::principalComponents() {

  auto[U, S, Vt] = LinAlg::SVD(LinAlg::cov(inputSet));
  X_normalized = data.meanCentering(inputSet);
  U_reduce.resize(U.size());
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < U.size(); j++) {
      U_reduce[j].push_back(U[j][i]);
    }
  }
  Z = LinAlg::matmult(LinAlg::transpose(U_reduce), X_normalized);
  return Z;
}

// Simply tells us the percentage of variance maintained.
double PCA::score() {
  std::vector<std::vector<double>> X_approx = LinAlg::matmult(U_reduce, Z);
  double num, den = 0;
  for (int i = 0; i < X_normalized.size(); i++) {
    num += LinAlg::norm_sq(LinAlg::subtraction(X_normalized[i], X_approx[i]));
  }
  num /= X_normalized.size();
  for (int i = 0; i < X_normalized.size(); i++) {
    den += LinAlg::norm_sq(X_normalized[i]);
  }

  den /= X_normalized.size();
  if (den == 0) {
    den += 1e-10; // For numerical sanity as to not recieve a domain error
  }
  return 1 - num / den;
}
}
