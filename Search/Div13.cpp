//
// Created by 李汇川 on 2022/6/3.
//
#include <iostream>

using namespace std;

int a[10], n;
int b[100];

void judge(int k) {
    int x = 0;
    for (int i = 0; i <= k; i++) {
        x = x * 10 + b[i];
        x %= 13;
    }
    if (x == 0) {
        for (int i = 0; i <= k; i++)
            cout << b[i];
        cout << endl;
    }
}

void search(int k) {
    if (k == n)
        return;

    for (int i = 0; i < 10; i++)
        if (a[i]) {
            if (k == 0 && i == 0)
                continue;
            a[i]--;
            b[k] = i;
            judge(k);
            search(k + 1);
            b[k] = 0;
            a[i]++;
        }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    for (int i = 0; i < 10; i++) {
        cin >> a[i];
        n += a[i];
    }

    search(0);
}