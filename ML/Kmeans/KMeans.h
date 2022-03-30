//
// Created by 李汇川 on 2022/3/30.
//

#ifndef PLAY_WITH_ALGO_ML_KMEANS_KMEANS_H_
#define PLAY_WITH_ALGO_ML_KMEANS_KMEANS_H_

#include <vector>
#include <string>
namespace KMeans {
class KMeans {
 public:
  KMeans(std::vector<std::vector<double>> inputSet, int k, std::string init_type = "Default");
  std::vector<std::vector<double>> modelSetTest(std::vector<std::vector<double>> X);
  std::vector<double> modelTest(std::vector<double> x);
  void train(int epoch_num, bool UI = 1);
  double score();
  std::vector<double> silhouette_scores();
 private:

  void Evaluate();
  void computeMu();

  void centroidInitialization(int k);
  void kmeansppInitialization(int k);
  double Cost();

  std::vector<std::vector<double>> inputSet;
  std::vector<std::vector<double>> mu;
  std::vector<std::vector<double>> r;

  double euclideanDistance(std::vector<double> A, std::vector<double> B);

  double accuracy_threshold;
  int k;

  std::string init_type;
}
};
#endif //PLAY_WITH_ALGO_ML_KMEANS_KMEANS_H_
