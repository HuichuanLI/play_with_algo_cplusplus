//
// Created by lhc456 on 2022/6/26.
//
//
// Created by lhc456 on 2022/6/26.
//
#include<iostream>
#include <fstream>
#include <ctime>
#include <queue>
#include "map"

using namespace std;
map<int, int> hashState;
bool isAnswerFound = false;
int stateCount, limit, maxDepth = 0;
long tstart;


struct PuzzleState {
    int puzzle[9];
    int depth, f;

    void calcHeuristic(PuzzleState ps) {
        int res = 0;
        int pos1[9], pos2[9];
        for (int i = 0; i < 9; i++) {
            pos1[puzzle[i]] = i;
            pos2[ps.puzzle[i]] = i;
        }
        for (int i = 0; i < 9; i++) {
            int x1 = pos1[i] / 3;
            int y1 = pos1[i] % 3;
            int x2 = pos2[i] / 3;
            int y2 = pos2[i] % 3;
            res += abs(x1 - x2) + abs(y1 - y2);
        }
        f = depth + res;
    }

} sp, ep;


int getPermutationHash(int perm[9]) {
    const int fact[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
    int res = 0;
    for (int i = 0; i < 9; i++) {
        int t = 0;
        for (int j = 0; j < i; j++)
            if (perm[j] > perm[i])
                t++;
        res += t * fact[i];
    }
    return res;
}


long getTime() {
    clock_t startTime = clock();

    return double(startTime) / CLOCKS_PER_SEC;

}


void printResult(int depth, int stateCount, long tstart, long tend) {
    cout << "Total steps: " << depth << endl;
    cout << "Total states: " << stateCount << endl;
    cout << "Maximum states in memory: " << maxDepth << endl;
    cout << "Total run time: " << (tend - tstart + 0.0) / 1000 << endl;
}

bool isSameBoard(int a[9], int b[9]) {
    for (int i = 0; i < 9; i++)
        if (a[i] != b[i])
            return false;
    return true;
}

void dfs(PuzzleState state) {
    stateCount++;
    maxDepth = max(maxDepth, state.depth);
    if (isSameBoard(state.puzzle, ep.puzzle)) {
        printResult(state.depth, stateCount, tstart, getTime());
        isAnswerFound = true;
        return;
    }
    if (state.f > limit)
        return;

    int p = 0;
    while (state.puzzle[p] != 0)
        p++;
    for (int i = 0; i < 4; i++) {
        int newPuzzle[9];
        memcpy(newPuzzle, state.puzzle, sizeof(newPuzzle));
        int rp = -1;
        if (i == 0 && p < 6)
            rp = p + 3;
        if (i == 1 && p > 2)
            rp = p - 3;
        if (i == 2 && p % 3 != 2)
            rp = p + 1;
        if (i == 3 && p % 3 != 0)
            rp = p - 1;
        if (rp == -1)
            continue;
        newPuzzle[p] = newPuzzle[rp];
        newPuzzle[rp] = 0;
        long permHash = getPermutationHash(newPuzzle);
        if (hashState.count(permHash))
            continue;
        hashState[permHash] = state.depth + 1;
        PuzzleState ps;
        ps.depth = state.depth + 1;
        memcpy(ps.puzzle, newPuzzle, sizeof(ps.puzzle));
        ps.calcHeuristic(ep);
        dfs(ps);
        if (isAnswerFound)
            return;
    }
}

void idastar_init() {
    stateCount = 0;
    tstart = getTime();
    limit = 0;
    while (true) {
        limit++;
        hashState.clear();
        hashState[getPermutationHash(sp.puzzle)] = 0;
        dfs(sp);
        if (isAnswerFound)
            break;
    }
}

int main() {
    ios::sync_with_stdio(false);
    ifstream fin("/Users/lhc456/Desktop/c++/play_with_algo_cplusplus/Search/searchadavnced/data/astar/1.in");
    cout.tie(NULL);

    sp.depth = 0;
    for (int i = 0; i < 9; i++)
        fin >> sp.puzzle[i];
    for (int i = 0; i < 9; i++)
        fin >> ep.puzzle[i];
    fin.close();

    sp.calcHeuristic(ep);
    idastar_init();
    return 0;
}