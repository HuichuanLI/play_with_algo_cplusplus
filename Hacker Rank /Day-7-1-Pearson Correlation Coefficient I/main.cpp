//
// Created by 李汇川 on 2022/5/29.
//
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

double mean(double x[], int n)
{
  double res = 0.0;
  for(int i = 0; i < n; i++)
    res += x[i];
  return res / n;
}

double sdev(double x[], int n, double m)
{
  double res = 0.0;
  for(int i = 0; i < n; i++)
    res += (x[i] - m)*(x[i] - m);
  return sqrt(res / n);
}

double corCoef(double x[], double y[], int n)
{
  double mx = mean(x, n);
  double my = mean(y, n);
  double sdx = sdev(x, n, mx);
  double sdy = sdev(y, n, my);
  double res = 0.0;
  for(int i = 0; i < n; i++)
    res += (x[i] - mx)*(y[i] - my);
  return res / (n*sdx*sdy);
}


int main(void)
{
  int n;
  cin >> n;
  double x[n];
  double y[n];
  for(int i = 0; i < n; i++)
    cin >> x[i];
  for(int i = 0; i < n; i++)
    cin >> y[i];
  cout << fixed << setprecision(3);
  cout << corCoef(x, y, n) << endl;
  return 0;
}