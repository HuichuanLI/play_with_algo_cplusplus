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
        sum += LinAlg::euclideanDistance(inputSet[j], mu[k]);
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
  double sum = 0;
  for (int i = 0; i < r.size(); i++) {
    for (int j = 0; j < r[0].size(); j++) {
      sum += r[i][j] * LinAlg::norm_sq(LinAlg::subtraction(inputSet[i], mu[j]));
    }
  }
  return sum;
}

// This simply computes or re-computes mu_k
void KMeans::computeMu() {
  for (int i = 0; i < mu.size(); i++) {
    std::vector<double> num;
    num.resize(r.size());

    for (int i = 0; i < num.size(); i++) {
      num[i] = 0;
    }

    double den = 0;
    for (int j = 0; j < r.size(); j++) {
      num = LinAlg::addition(num, LinAlg::scalarMultiply(r[j][i], inputSet[j]));
    }
    for (int j = 0; j < r.size(); j++) {
      den += r[j][i];
    }
    mu[i] = LinAlg::scalarMultiply(double(1) / double(den), num);
  }

}

// This simply computes r_nk
void KMeans::Evaluate() {
  r.resize(inputSet.size());

  for (int i = 0; i < r.size(); i++) {
    r[i].resize(k);
  }

  for (int i = 0; i < r.size(); i++) {
    std::vector<double> closestCentroid = mu[0];
    for (int j = 0; j < r[0].size(); j++) {
      bool isCentroidCloser =
          LinAlg::euclideanDistance(inputSet[i], mu[j]) < LinAlg::euclideanDistance(inputSet[i], closestCentroid);
      if (isCentroidCloser) {
        closestCentroid = mu[j];
      }
    }
    for (int j = 0; j < r[0].size(); j++) {
      if (mu[j] == closestCentroid) {
        r[i][j] = 1;
      } else { r[i][j] = 0; }
    }
  }

}

void CostInfo(int epoch, double cost_prev, double Cost) {
  std::cout << "-----------------------------------" << std::endl;
  std::cout << "This is epoch: " << epoch << std::endl;
  std::cout << "The cost function has been minimized by " << cost_prev - Cost << std::endl;
  std::cout << "Current Cost:" << std::endl;
  std::cout << Cost << std::endl;
}

void KMeans::train(int epoch_num, bool UI) {
  double cost_prev = 0;
  int epoch = 1;

  Evaluate();

  while (true) {
    
    cost_prev = Cost();

    computeMu();
    Evaluate();

    // UI PORTION
    if (UI) { CostInfo(epoch, cost_prev, Cost()); }
    epoch++;

    if (epoch > epoch_num) { break; }

  }
}

std::vector<std::vector<double>> KMeans::modelSetTest(std::vector<std::vector<double>> X) {
  std::vector<std::vector<double>> closestCentroids;
  for (int i = 0; i < inputSet.size(); i++) {
    std::vector<double> closestCentroid = mu[0];
    for (int j = 0; j < r[0].size(); j++) {
      bool isCentroidCloser = LinAlg::euclideanDistance(X[i], mu[j]) < LinAlg::euclideanDistance(X[i], closestCentroid);
      if (isCentroidCloser) {
        closestCentroid = mu[j];
      }
    }
    closestCentroids.push_back(closestCentroid);
  }
  return closestCentroids;
}
std::vector<double> KMeans::silhouette_scores() {
  std::vector<std::vector<double>> closestCentroids = modelSetTest(inputSet);
  std::vector<double> silhouette_scores;
  for (int i = 0; i < inputSet.size(); i++) {
    // COMPUTING a[i]
    double a = 0;
    for (int j = 0; j < inputSet.size(); j++) {
      if (i != j && r[i] == r[j]) {
        a += LinAlg::euclideanDistance(inputSet[i], inputSet[j]);
      }
    }
    // NORMALIZE a[i]
    a /= closestCentroids[i].size() - 1;


    // COMPUTING b[i]
    double b = INT_MAX;
    for (int j = 0; j < mu.size(); j++) {
      if (closestCentroids[i] != mu[j]) {
        double sum = 0;
        for (int k = 0; k < inputSet.size(); k++) {
          sum += LinAlg::euclideanDistance(inputSet[i], inputSet[k]);
        }
        // NORMALIZE b[i]
        double k_clusterSize = 0;
        for (int k = 0; k < closestCentroids.size(); k++) {
          if (closestCentroids[k] == mu[j]) {
            k_clusterSize++;
          }
        }
        if (sum / k_clusterSize < b) { b = sum / k_clusterSize; }
      }
    }
    silhouette_scores.push_back((b - a) / fmax(a, b));
  }
  return silhouette_scores;
}
}

int main() {
  // KMeans
  std::vector<std::vector<double>> inputSet = {{32, 0, 7}, {2, 28, 17}, {0, 9, 23}};
  KMeans::KMeans kmeans(inputSet, 3, "KMeans++");
  kmeans.train(3, 1);
  std::cout << std::endl;
  LinAlg::printMatrix(kmeans.modelSetTest(inputSet)); // Returns the assigned centroids to each of the respective training examples
  std::cout << std::endl;
  LinAlg::printVector(kmeans.silhouette_scores());
}