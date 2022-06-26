//
// Created by lhc456 on 2022/6/26.
//
#include<iostream>
#include <fstream>

using namespace std;

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

char maze[102][102];
int minTurns[102][102][4], pre[102][102][4][3];
int res[1002][2];
int n, head, tail, resTurns = INT_MAX, stateCount = 0, level;

void updateResult(int x, int y, int dir) {
    int tmpRes[1002][2];
    int turns = 0;
    tmpRes[0][0] = x;
    tmpRes[0][1] = y;
    while (x != 1 || y != 1) {
        int tx = pre[x][y][dir][0];
        int ty = pre[x][y][dir][1];
        dir = pre[x][y][dir][2];
        tmpRes[++turns][0] = tx;
        tmpRes[turns][1] = ty;
        x = tx;
        y = ty;
    }

    if (turns < resTurns) {
        memcpy(res, tmpRes, sizeof(int) * 2 * (turns + 1));
        resTurns = turns;
    }
}

void dfs(int x, int y, int dir, int turns) {

    int tx = x, ty = y;
    stateCount++;
    while (true) {
        tx += dx[dir];
        ty += dy[dir];
        if (maze[tx][ty] == '*')
            break;
        if (tx == n && ty == n) {
            updateResult(x, y, dir);
            return;
        }
        for (int i = 0; i < 2; i++) {
            int id = (dir + 3 - i * 2) % 4;
            if (maze[tx + dx[id]][ty + dy[id]] == '.' && minTurns[tx][ty][id] > turns + 1) {
                minTurns[tx][ty][id] = turns + 1;
                pre[tx][ty][id][0] = x;
                pre[tx][ty][id][1] = y;
                pre[tx][ty][id][2] = dir;
                dfs(tx, ty, id, turns + 1);
            }
        }
    }
}

void dfs_init() {
    level = -1;
    while (true) {
        level++;
        memset(minTurns, 10, sizeof(minTurns));
        memset(pre, 0, sizeof(pre));
        minTurns[1][1][0] = -1;
        minTurns[1][1][1] = -1;
        dfs(1, 1, 0, -1); // 东
        dfs(1, 1, 1, -1);//南
        if (resTurns != INT_MAX)
            break;
    }
}


int main() {
    ios::sync_with_stdio(false);
    ifstream fin("/Users/lhc456/Desktop/c++/play_with_algo_cplusplus/Search/searchadavnced/data/1.in");
    cout.tie(NULL);

    fin >> n;
    for (int i = 0; i <= n + 1; i++) {
        string s;
        fin >> s;
        for (int j = 0; j <= n + 1; j++)
            maze[i][j] = s[j];
    }
    fin.close();

    dfs_init();

    for (int i = resTurns; i >= 0; i--)
        cout << '(' << res[i][0] << ',' << res[i][1] << ") --> ";
    cout << '(' << n << ',' << n << ')' << endl;
    cout << "Total states: " << stateCount << endl;

    return 0;
}