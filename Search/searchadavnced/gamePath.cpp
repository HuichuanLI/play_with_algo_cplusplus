//
// Created by lhc456 on 2022/6/26.
//

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

const int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};

int hashState[1001][1001];
int pre[1001][1001];
char gameBoard[1001][1001];
int n, m, xs, ys, xe, ye;
int tstart;

struct GameState {
    int x, y, g, f;

    void calcHeuristic(int ex, int ey) {
        int deltaX = abs(ex - x);
        int deltaY = abs(ey - y);
        if (deltaX > deltaY)
            f = g + 14 * deltaY + 10 * (deltaX - deltaY);
        else
            f = g + 14 * deltaX + 10 * (deltaY - deltaX);
    }

    bool operator<(const GameState &gs) const {
        return f > gs.f;
    }
};

long getTime() {
    clock_t startTime = clock();
    return double(startTime) / CLOCKS_PER_SEC;
}

void printResult(int pathLength, int stateCount, bool printBoard) {
    cout << "Path length:" << pathLength << endl;
    cout << "Total states:" << stateCount << endl;
    cout << "Total run time:" << getTime() - tstart << "ms" << endl;
    if (!printBoard)
        return;
    int x = xe, y = ye;
    while (x != xs || y != ys) {
        gameBoard[xs][ys] = '1';
        int t = pre[x][y];
        x -= dx[t];
        y -= dy[t];
    }
    gameBoard[xs][ys] = 'S';
    gameBoard[xe][ye] = 'E';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << gameBoard[i][j];
        }
        cout << endl;
    }

}

void astar() {
    int stateCount = 0;
    memset(hashState, 11, sizeof(hashState));
    hashState[xs][ys] = 0;
    priority_queue<GameState, vector<GameState>> pq;

    GameState initState;
    initState.x = xs;
    initState.y = ys;
    initState.g = 0;

    initState.calcHeuristic(xe, ye);
    pq.push(initState);

    while (!pq.empty()) {
        GameState state = pq.top();
        stateCount++;
        pq.pop();

        for (int i = 0; i < 8; i++) {
            int tx = state.x + dx[i];
            int ty = state.y + dy[i];

            int tg = state.g + ((i % 2) ? 14 : 10);
            if (tx < 0 || tx >= n || ty < 0 || ty >= m || gameBoard[tx][ty] == '#' || hashState[tx][ty] <= tg)
                continue;
            hashState[tx][ty] = tg;
            pre[tx][ty] = i;

            if (tx == xe && ty == ye) {
                printResult(tg, stateCount + pq.size(), n <= 20);
                return;
            }

            GameState tempState;
            tempState.x = tx;
            tempState.y = ty;
            tempState.g = tg;
            tempState.calcHeuristic(xe, ye);
            pq.push(tempState);
        }
    }

}


int main() {
    ios::sync_with_stdio(false);
    ifstream fin("/Users/lhc456/Desktop/c++/play_with_algo_cplusplus/Search/searchadavnced/data/agame/1.in");
    cout.tie(NULL);

    fin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s;
        fin >> s;
        for (int j = 0; j < m; j++)
            gameBoard[i][j] = s[j];
    }


    fin >> xs >> ys >> xe >> ye;
    fin.close();


    tstart = getTime();
    astar();
    return 0;

}