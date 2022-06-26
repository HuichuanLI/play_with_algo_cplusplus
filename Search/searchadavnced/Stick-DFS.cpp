//
// Created by lhc456 on 2022/6/26.
//
#include <iostream>

using namespace std;

int stick[100];
bool marked[100];
int n, sum = 0, stickN, stickLen;
bool findAnswer = false;

void dfs(int k, int l, int s) {
    if (k == stickN - 1) {
        findAnswer = true;
        return;
    }
    if (l == stickLen)
        dfs(k + 1, 0, -1);

    int prei = -1;
    for (int i = s + 1; i < n; i++)
        if (!marked[i] && l + stick[i] <= stickLen) {
            if (prei > -1 && stick[i] == stick[prei])
                continue;
            prei = i;
            marked[i] = true;
            dfs(k, l + stick[i], i);
            marked[i] = false;
            if ((l == 0 || l + stick[i] == stickLen) && !findAnswer)
                return;
            if (findAnswer)
                return;
        }
}

int main() {
    ios::sync_with_stdio(false);
    ifstream fin("data/stick/4.in");
    cout.tie(NULL);

    fin >> n;
    int maxStick = 0;
    for (int i = 0; i < n; i++) {
        fin >> stick[i];
        sum += stick[i];
        maxStick = max(maxStick, stick[i]);
    }
    fin.close();

    sort(stick, stick + n, greater<int>());

    for (stickLen = maxStick; stickLen <= sum / 2; stickLen++) {
        if (sum % stickLen)
            continue;
        stickN = sum / stickLen;
        dfs(0, 0, -1);
        if (findAnswer) {
            cout << stickLen << endl;
            break;
        }
    }

    if (!findAnswer)
        cout << sum << endl;
    return 0;
}