#include <iostream>
#include<ctime>
using namespace std;

long long fac(int n) {
  if (n < 0)
    return -1;
  else if (n == 0 || n == 1)
    return 1;
  else
    return n * fac(n - 1);
}

int main() {
  time_t s, e, sumtime;
  int n;
  cin >> n;
  s = clock();
  cout << "fac(" << n << ")=" << fac(n) << endl;
  e = clock();
  sumtime = e - s;
  cout << "time:" << sumtime << endl;
  return 0;
}
