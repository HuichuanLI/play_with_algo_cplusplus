//
// Created by lhc456 on 2022/6/26.
//
#include<iostream>

using namespace std;

int n, c, res;
int b[30], e[30];
int sump[31];


void dfs(int sumb, int sume, int k) {
    if (sumb + sume + sump[k] < c)
        return;

    if (sumb + sume >= c) {
        res = min(res, abs(sumb - sume));
        if (res == 0)
            return;
    }
    if (k == n)
        return;

    for (int i = 0; i < 2; i++) {
        int tsumb = sumb + b[k] * i;
        int tsume = sume + e[k] * i;
        dfs(tsumb, tsume, k + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> c;
    for (int i = 0; i < n; i++)
        cin >> b[i] >> e[i];

    memset(sump, 0, sizeof(sump));
    for (int i = n - 1; i >= 0; i--) {
        sump[i] = sump[i + 1];
        if (b[i] + e[i] > 0)
            sump[i] += b[i] + e[i];
    }

    res = INT_MAX;

    dfs(0, 0, 0);

    if (res == INT_MAX)
        res = -1;
    cout << res << endl;
    return 0;

}