//
// Created by 李汇川 on 2022/3/19.
//
#include <iostream>
#include<iomanip>
#include<ctime>
using namespace std;

long long fib1(int n) {
  if (n < 1)
    return -1;
  else if (n == 1 || n == 2)
    return 1;
  else
    return fib1(n - 1) + fib1(n - 2);
}

long double fib2(int n) {
  long double temp;
  if (n < 1)
    return -1;
  long long *a = new long long[n + 1];
  a[1] = a[2] = 1;
  for (int i = 3; i <= n; i++) {
    a[i] = a[i - 1] + a[i - 2];
    cout << a[i] << endl;
  }
  temp = a[n];
  delete[]a;
  return temp;
}

int main() {
  time_t s, e, sumtime;
  int n;
  cin >> n;//10 30 50 100
  s = clock();
  //cout<<fixed<<setprecision(0);
  //cout<<"fib("<<n<<")="<<fib1(n)<<endl;
  cout << "fib(" << n << ")=" << fib2(n) << endl;
  e = clock();
  sumtime = e - s;
  cout << "time:" << sumtime << endl;
  return 0;
}
