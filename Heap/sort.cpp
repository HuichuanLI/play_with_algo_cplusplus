//
// Created by lhc456 on 2022/9/13.
//
#include<iostream>
#include <fstream>
#include <sys/time.h>


using namespace std;

int a[10000001];
int n, tstart, tend;

long getTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int main() {
    ios::sync_with_stdio(false);
    ifstream fin("5.in");
    ofstream fout("5-sorted.out");

    fin >> n;
    for (int i = 0; i < n; i++)
        fin >> a[i];
    fin.close();

    tstart = getTime();
    sort(a, a + n);
    for (int i = 0; i < n - 1; i++)
        fout << a[i] << ' ';
    fout << a[n - 1] << endl;
    tend = getTime();
    cout << "sort time:" << (tend - tstart + 0.0) / 1000 << endl;
    fout.close();
    return 0;
}