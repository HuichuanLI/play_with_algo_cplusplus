//
// Created by 李汇川 on 2021/11/23.
//

#include <cmath>
#include <iostream>

const int VN = 11;

const char *base_words[] =
    {
        "进攻", "炮弹", "射程", "榴弹炮", "发射", "口径", "迫击炮", "瞄准", "后坐力", "弹道", "目标"
    };

double CosSimilarity(double *va, double *vb, int vn) {
  double cossu = 0.0;
  double cossda = 0.0;
  double cossdb = 0.0;

  for (int i = 0; i < vn; i++) {
    cossu += va[i] * vb[i];
    cossda += va[i] * va[i];
    cossdb += vb[i] * vb[i];
  }

  return cossu / (std::sqrt(cossda) * std::sqrt(cossdb));
}
int main() {
  double v1[] = {0, 2, 1, 1, 1, 1, 0, 0, 0, 1, 1};
  double v2[] = {0, 2, 1, 1, 1, 1, 0, 1, 0, 2, 1};
  double v3[] = {1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0};

  double s1 = CosSimilarity(v1, v2, VN);
  double s2 = CosSimilarity(v1, v3, VN);
  double s3 = CosSimilarity(v2, v3, VN);

  std::cout << s1 << std::endl;
  std::cout << s2 << std::endl;
  std::cout << s3 << std::endl;

  return 0;
}