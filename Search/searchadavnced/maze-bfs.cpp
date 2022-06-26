//
// Created by lhc456 on 2022/6/26.
//
#include <iostream>
#include <fstream>

using namespace std;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

char maze[102][102];
int minTurns[102][102][4], pre[102][102][4][3];
int q[40001][4];   // 0: X  1: Y  2: Direction  3: Turns
int n, head, tail;

void printResult(int x, int y, int dir) {
    int res[40001][2];
    int turns = 0;
    res[0][0] = x;
    res[0][1] = y;
    while (x != 1 || y != 1) {
        int tx = pre[x][y][dir][0];
        int ty = pre[x][y][dir][1];
        dir = pre[x][y][dir][2];
        res[++turns][0] = tx;
        res[turns][1] = ty;
        x = tx;
        y = ty;
    }

    for (int i = turns; i >= 0; i--)
        cout << '(' << res[i][0] << ',' << res[i][1] << ") --> ";
    cout << '(' << n << ',' << n << ')' << endl;
}


void bfs() {
    memset(q, 0, sizeof(q));
    memset(minTurns, 10, sizeof(minTurns));
    memset(pre, 0, sizeof(pre));
    q[0][0] = 1;
    q[0][1] = 1;
    q[0][2] = 0;  // East
    q[0][3] = -1;
    q[1][0] = 1;
    q[1][1] = 1;
    q[1][2] = 1;  // South
    q[1][3] = -1;
    head = 0;
    tail = 1;
    minTurns[1][1][0] = -1;
    minTurns[1][1][1] = -1;

    while (head <= tail) {
        int x = q[head][0];
        int y = q[head][1];
        int dir = q[head][2];
        int turns = q[head++][3];
        int tx = x;
        int ty = y;

        while (true) {
            tx += dx[dir];
            ty += dy[dir];
            if (maze[tx][ty] == '*')
                break;
            if (tx == n && ty == n) {
                printResult(x, y, dir);
                return;
            }
            for (int i = 0; i < 2; i++) {
                int id = (dir + 3 - i * 2) % 4;
                if (maze[tx + dx[id]][ty + dy[id]] == '.' && minTurns[tx][ty][id] > turns + 1) {
                    q[++tail][0] = tx;
                    q[tail][1] = ty;
                    q[tail][2] = id;
                    q[tail][3] = turns + 1;
                    minTurns[tx][ty][id] = turns + 1;
                    pre[tx][ty][id][0] = x;
                    pre[tx][ty][id][1] = y;
                    pre[tx][ty][id][2] = dir;
                }
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    ifstream fin("/Users/lhc456/Desktop/c++/play_with_algo_cplusplus/Search/searchadavnced/data/2.in");
    cout.tie(NULL);

    fin >> n;
    for (int i = 0; i <= n + 1; i++) {
        string s;
        fin >> s;
        for (int j = 0; j <= n + 1; j++)
            maze[i][j] = s[j];
    }
    fin.close();

    bfs();

    cout << "Total States: " << tail << endl;
    return 0;
}