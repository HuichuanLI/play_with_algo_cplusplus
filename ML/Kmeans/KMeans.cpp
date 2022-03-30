//
// Created by 李汇川 on 2022/3/30.
//

#include "KMeans.h"
#include "../LinAlg/LinAlg.h"
#include <iostream>
#include <random>
#include <climits>

namespace KMeans {

void KMeans::centroidInitialization(int k) {
  mu.resize(k);

  for (int i = 0; i < k; i++) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(0, int(inputSet.size() - 1));

    mu[i].resize(inputSet.size());
    mu[i] = inputSet[distribution(generator)];
  }
}

KMeans::KMeans(std::vector<std::vector<double>> inputSet, int k, std::string init_type)
    : inputSet(inputSet), k(k), init_type(init_type) {
  if (init_type == "KMeans++") {
    kmeansppInitialization(k);
  } else {
    centroidInitialization(k);
  }
}

void KMeans::kmeansppInitialization(int k) {
  LinAlg::LinAlg alg;
  std::random_device rd;
  std::default_random_engine generator(rd());
  std::uniform_int_distribution<int> distribution(0, int(inputSet.size() - 1));
  mu.push_back(inputSet[distribution(generator)]);

  for (int i = 0; i < k - 1; i++) {
    std::vector<double> farthestCentroid;
    for (int j = 0; j < inputSet.size(); j++) {
      double max_dist = 0;
      /* SUM ALL THE SQUARED DISTANCES, CHOOSE THE ONE THAT'S FARTHEST
      AS TO SPREAD OUT THE CLUSTER CENTROIDS. */
      double sum = 0;
      for (int k = 0; k < mu.size(); k++) {
        sum += alg.euclideanDistance(inputSet[j], mu[k]);
      }
      if (sum * sum > max_dist) {
        farthestCentroid = inputSet[j];
        max_dist = sum * sum;
      }
    }
    mu.push_back(farthestCentroid);
  }
}

double KMeans::Cost() {
  LinAlg::LinAlg alg;
  double sum = 0;
  for (int i = 0; i < r.size(); i++) {
    for (int j = 0; j < r[0].size(); j++) {
      sum += r[i][j] * alg.norm_sq(alg.subtraction(inputSet[i], mu[j]));
    }
  }
  return sum;
}

// This simply computes or re-computes mu_k
void KMeans::computeMu() {
  LinAlg::LinAlg alg;
  for (int i = 0; i < mu.size(); i++) {
    std::vector<double> num;
    num.resize(r.size());

    for (int i = 0; i < num.size(); i++) {
      num[i] = 0;
    }

    double den = 0;
    for (int j = 0; j < r.size(); j++) {
      num = alg.addition(num, alg.scalarMultiply(r[j][i], inputSet[j]));
    }
    for (int j = 0; j < r.size(); j++) {
      den += r[j][i];
    }
    mu[i] = alg.scalarMultiply(double(1) / double(den), num);
  }

}


void KMeans::train(int epoch_num, bool UI) {
  double cost_prev = 0;
  int epoch = 1;

  Evaluate();

  while (true) {

    // STEPS OF THE ALGORITHM
    // 1. DETERMINE r_nk
    // 2. DETERMINE J
    // 3. DETERMINE mu_k

    // STOP IF CONVERGED, ELSE REPEAT

    cost_prev = Cost();

    computeMu();
    Evaluate();

    // UI PORTION
    if (UI) { Utilities::CostInfo(epoch, cost_prev, Cost()); }
    epoch++;

    if (epoch > epoch_num) { break; }

  }
}
}

int main() {
  // KMeans
  std::vector<std::vector<double>> inputSet = {{32, 0, 7}, {2, 28, 17}, {0, 9, 23}};
  KMeans::KMeans kmeans(inputSet, 3, "KMeans++");
  kmeans.train(3, 1);
  std::cout << std::endl;
  LinAlg::LinAlg alg;
  alg.printMatrix(kmeans.modelSetTest(inputSet)); // Returns the assigned centroids to each of the respective training examples
  std::cout << std::endl;
  alg.printVector(kmeans.silhouette_scores());
}