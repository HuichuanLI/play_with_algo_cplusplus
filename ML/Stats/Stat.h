//
// Created by 李汇川 on 2022/3/30.
//

#ifndef PLAY_WITH_ALGO_ML_STATS_STAT_H_
#define PLAY_WITH_ALGO_ML_STATS_STAT_H_

#include <algorithm>
#include <map>
#include <cmath>
#include <iostream>
#include "vector"
#include "../LinAlg/LinAlg.h"
namespace Stat {

double mean(const std::vector<double> &x) {
  double sum = 0;
  for (int i = 0; i < x.size(); i++) {
    sum += x[i];
  }
  return sum / x.size();
}

double median(std::vector<double> x) {
  double center = double(x.size()) / double(2);
  sort(x.begin(), x.end());
  if (x.size() % 2 == 0) {
    return mean({x[center - 1], x[center]});
  } else {
    return x[center - 1 + 0.5];
  }
}

double range(const std::vector<double> &x) {
  return LinAlg::max(x) - LinAlg::min(x);
}

double midrange(const std::vector<double> &x) {
  return range(x) / 2;
}

double absAvgDeviation(const std::vector<double> &x) {
  double sum = 0;
  double mean_x = mean(x);
  for (int i = 0; i < x.size(); i++) {
    sum += std::abs(x[i] - mean_x);
  }
  return sum / x.size();
}

double variance(const std::vector<double> &x) {
  double sum = 0;
  for (int i = 0; i < x.size(); i++) {
    sum += (x[i] - mean(x)) * (x[i] - mean(x));
  }
  return sum / (x.size() - 1);
}

double standardDeviation(const std::vector<double> &x) {
  return std::sqrt(variance(x));
}

double covariance(const std::vector<double> &x, const std::vector<double> &y) {
  double sum = 0;
  for (int i = 0; i < x.size(); i++) {
    sum += (x[i] - mean(x)) * (y[i] - mean(y));
  }
  return sum / (x.size() - 1);
}

double correlation(const std::vector<double> &x, const std::vector<double> &y) {
  return covariance(x, y) / (standardDeviation(x) * standardDeviation(y));
}

double R2(const std::vector<double> &x, const std::vector<double> &y) {
  return correlation(x, y) * correlation(x, y);
}
}

#endif //PLAY_WITH_ALGO_ML_STATS_STAT_H_
