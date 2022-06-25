//
// Created by lhc456 on 2022/6/26.
//
#include<iostream>
using namespace std;

const int deltaX[4] = {1, 0, -1 ,0};
const int deltaY[4] = {0, 1, 0, -1};

int n, m;
int maze[100][100];
bool hashState[100][100];
int pathX[10000], pathY[10000];
int startX, startY, endX, endY;
bool findAnswer = false;

void dfs(int x, int y, int step) {
    if (x == endX && y == endY) {
        findAnswer = true;
        for (int i = 0; i < step; i++)
            cout << "(" << pathX[i] << ", " << pathY[i] << ")";
        return;
    }

    for (int i = 0; i < 4; i++) {
        int tx = x + deltaX[i];
        int ty = y + deltaY[i];
        pathX[step] = tx;
        pathY[step] = ty;
        if (tx < 1 || tx > n || ty < 1 || ty > m || maze[tx][ty])
            continue;
        if (hashState[tx][ty])
            continue;
        hashState[tx][ty] = true;
        dfs(tx, ty, step + 1);
        if (findAnswer)
            break;
    }
}

void dfs_init() {
    memset(hashState, 0, sizeof(hashState));
    hashState[startX][startY] = true;
    dfs(startX, startY, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> maze[i][j];
    cin >> startX >> startY >> endX >> endY;

    dfs_init();

    return 0;
}