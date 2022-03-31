//
// Created by 李汇川 on 2022/3/30.
//
#pragma once
#include <iostream>
#include <random>
#include <map>
#include <cmath>

namespace LinAlg {

double norm_sq(std::vector<double> a) {
  double n_sq = 0;
  for (int i = 0; i < a.size(); i++) {
    n_sq += a[i] * a[i];
  }
  return n_sq;
}

std::vector<double> subtraction(std::vector<double> a, std::vector<double> b) {
  std::vector<double> c;
  c.resize(a.size());
  for (int i = 0; i < a.size(); i++) {
    c[i] = a[i] - b[i];
  }
  return c;
}

// Multidimensional Euclidean Distance
double euclideanDistance(std::vector<double> a, std::vector<double> b) {
  double dist = 0;
  for (int i = 0; i < a.size(); i++) {
    dist += (a[i] - b[i]) * (a[i] - b[i]);
  }
  return std::sqrt(dist);
}

void printMatrix(std::vector<std::vector<double>> A) {
  for (int i = 0; i < A.size(); i++) {
    for (int j = 0; j < A[i].size(); j++) {
      std::cout << A[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void printVector(std::vector<double> a) {
  for (int i = 0; i < a.size(); i++) {
    std::cout << a[i] << " ";
  }
  std::cout << std::endl;
}

std::vector<double> addition(std::vector<double> a, std::vector<double> b) {
  std::vector<double> c;
  c.resize(a.size());
  for (int i = 0; i < a.size(); i++) {
    c[i] = a[i] + b[i];
  }
  return c;
}

double max(std::vector<double> a) {
  int max = a[0];
  for (int i = 0; i < a.size(); i++) {
    if (a[i] > max) {
      max = a[i];
    }
  }
  return max;
}

double min(std::vector<double> a) {
  int min = a[0];
  for (int i = 0; i < a.size(); i++) {
    if (a[i] < min) {
      min = a[i];
    }
  }
  return min;
}
std::vector<double> scalarMultiply(double scalar, std::vector<double> a) {
  for (int i = 0; i < a.size(); i++) {
    a[i] *= scalar;
  }
  return a;
}

};