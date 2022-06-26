//
// Created by lhc456 on 2022/6/26.
//
#include<iostream>

using namespace std;

int q[513], step[513];
int hashState[513];
int head, tail;

int getHash(int state) {
    int res = 0;
    for (int i = 0; i < 9; i++) {
        res = res * 2 + state % 10;
        state = state / 10;
    }
    return res;
}

int getNewState(int state, int op) {
    int tmp[9];
    for (int i = 0; i < 9; i++) {
        tmp[8 - i] = state % 10;
        state /= 10;
    }

    tmp[op] = 1 - tmp[op];
    if (op % 3 != 0)
        tmp[op - 1] = 1 - tmp[op - 1];
    if (op % 3 != 2)
        tmp[op + 1] = 1 - tmp[op + 1];
    if (op > 2)
        tmp[op - 3] = 1 - tmp[op - 3];
    if (op < 6)
        tmp[op + 3] = 1 - tmp[op + 3];

    int res = 0;
    for (int i = 0; i < 9; i++)
        res = res * 10 + tmp[i];
    return res;
}

int bfs(int initState) {
    memset(q, 0, sizeof(q));
    memset(step, 0, sizeof(step));
    q[0] = initState;
    step[0] = 0;
    head = 0;
    tail = 0;
    memset(hashState, 0, sizeof(hashState));
    hashState[getHash(initState)] = true;

    while (head <= tail) {
        int state = q[head];
        int stateStep = step[head];
        head++;

        for (int i = 0; i < 9; i++) {
            int tempState = getNewState(state, i);
            int tempStep = stateStep + 1;
            int tempStateHash = getHash(tempState);
            if (hashState[tempStateHash])
                continue;
            hashState[tempStateHash] = true;
            if (tempState == 111111111)
                return tempStep;
            q[++tail] = tempState;
            step[tail] = tempStep;
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int initState = 0, tmp;
    for (int i = 0; i < 9; i++) {
        cin >> tmp;
        initState = initState * 10 + tmp;
    }

    cout << bfs(initState) << endl;
    return 0;
}