//
// Created by 李汇川 on 2022/3/30.
//

#include "Stat.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include "Stat.h"
#include "../LinAlg/LinAlg.h"

int main() {
  // // STATISTICS
  std::vector<double> x = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<double> y = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  std::vector<double> w = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};

  std::cout << "Arithmetic Mean: " << Stat::mean(x) << std::endl;
  std::cout << "Median: " << Stat::median(x) << std::endl;
  LinAlg::printVector(x);

  std::cout << "Range: " << Stat::range(x) << std::endl;
  std::cout << "Midrange: " << Stat::midrange(x) << std::endl;
  std::cout << "Absolute Average Deviation: " << Stat::absAvgDeviation(x) << std::endl;
  std::cout << "Standard Deviation: " << Stat::standardDeviation(x) << std::endl;
  std::cout << "Variance: " << Stat::variance(x) << std::endl;
  std::cout << "Covariance: " << Stat::covariance(x, y) << std::endl;
  std::cout << "Correlation: " << Stat::correlation(x, y) << std::endl;
  std::cout << "R^2: " << Stat::R2(x, y) << std::endl;

  std::cout << "Root Mean Square (Quadratic mean): " << Stat::RMS(x) << std::endl;
  std::cout << "Power Mean (p = 5): " << Stat::powerMean(x, 5) << std::endl;
  std::cout << "Weighted Mean: " << Stat::weightedMean(x, w) << std::endl;
  std::cout << "Geometric Mean: " << Stat::geometricMean(x) << std::endl;

}