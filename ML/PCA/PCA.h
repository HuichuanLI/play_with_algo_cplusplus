//
// Created by 李汇川 on 2022/4/1.
//

#ifndef PLAY_WITH_ALGO_ML_PCA_PCA_H_
#define PLAY_WITH_ALGO_ML_PCA_PCA_H_
#include <vector>

namespace PCA {
class PCA {

 public:
  PCA(std::vector<std::vector<double>> inputSet, int k);
  std::vector<std::vector<double>> principalComponents();
  double score();
 private:
  std::vector<std::vector<double>> inputSet;
  std::vector<std::vector<double>> X_normalized;
  std::vector<std::vector<double>> U_reduce;
  std::vector<std::vector<double>> Z;
  int k;
};
}
#endif //PLAY_WITH_ALGO_ML_PCA_PCA_H_
