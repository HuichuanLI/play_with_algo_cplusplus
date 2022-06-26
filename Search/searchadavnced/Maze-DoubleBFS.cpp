//
// Created by lhc456 on 2022/6/26.
//
#include <iostream>
#include <fstream>
#include "queue"

using namespace std;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

// 迷宫
char maze[102][102];
// 记录最小拐弯次数和前驱态的两个哈希表，正向
int minTurns[102][102][4], pre[102][102][4][3];
// 记录最小拐弯次数和前驱态的两个哈希表，反向
int minTurns2[102][102][4], pre2[102][102][4][3];
int n, head, tail, head2, tail2;


struct pos {
    int x;
    int y;
    int direction;
    int turns;
};


// 倒推路径，输出结果的函数
void printResult(int x, int y, int dir, int dir2) {
    int res[40001][2];
    int turns = 0;
    int x2 = x;
    int y2 = y;
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

    while (true) {
        int tx = pre2[x2][y2][dir2][0];
        int ty = pre2[x2][y2][dir2][1];
        dir2 = pre2[x2][y2][dir2][2];
        if (tx == n && ty == n)
            break;
        cout << '(' << tx << ',' << ty << ") --> ";
        x2 = tx;
        y2 = ty;
    }
    cout << '(' << n << ',' << n << ')' << endl;
}

void double_bfs() {
    memset(minTurns, 10, sizeof(minTurns));
    memset(pre, 0, sizeof(pre));

    queue<pos> q1;
    queue<pos> q2;

    pos pos1;
    pos1.x = 1;
    pos1.y = 1;
    pos1.direction = 0;
    pos1.turns = -1;
    q1.push(pos1);


    pos pos2;
    pos2.x = 1;
    pos2.y = 1;
    pos2.direction = 1;
    pos2.turns = -1;
    q1.push(pos2);

    minTurns[1][1][0] = -1;
    minTurns[1][1][1] = -1;

    memset(minTurns2, 10, sizeof(minTurns2));
    memset(pre2, 0, sizeof(pre2));

    pos pos3;
    pos3.x = n;
    pos3.y = n;
    pos3.direction = 0;
    pos3.turns = -1;
    q2.push(pos3);


    pos pos4;
    pos4.x = n;
    pos4.y = n;
    pos4.direction = 1;
    pos4.turns = -1;
    minTurns2[1][1][0] = -1;
    minTurns2[1][1][1] = -1;
    q2.push(pos4);

    int level = -2;

    while (!q1.empty() or !q2.empty()) {
        level++;
        while (q1.front().turns <= level) {
            pos temp = q1.front();
            q1.pop();
            int x = temp.x;
            int y = temp.y;
            int dir = temp.direction;
            int turns = temp.turns;
            int tx = x;
            int ty = y;
            while (true) {
                tx += dx[dir];
                ty += dy[dir];
                if (maze[tx][ty] == '*')
                    break;
                for (int i = 0; i < 2; i++) {
                    // 处理技巧：i = 0时id = dir左拐，i = 1时id = dir右拐
                    // 因为方向从0到3分别是东南西北
                    // 每个方向左拐都是(它的数字-1) % 4对应的方向，因为有可能减成负数所以再加4，等于+3后%4，结果一样
                    // 而每个方向右拐，都是(它的数字+1) % 4对应的方向
                    int id = (dir + 3 - i * 2) % 4;
                    if (maze[tx + dx[id]][ty + dy[id]] == '.' && minTurns[tx][ty][id] > turns + 1) {
                        tail += 1;
                        pos tempnextpos;
                        tempnextpos.x = tx;
                        tempnextpos.y = ty;
                        tempnextpos.direction = id;
                        tempnextpos.turns = turns + 1;
                        q1.push(pos(tempnextpos));

                        minTurns[tx][ty][id] = turns + 1;
                        pre[tx][ty][id][0] = x;
                        pre[tx][ty][id][1] = y;
                        pre[tx][ty][id][2] = dir;
                        // 如果遇到了反向来的相同状态，就意味着找到了一条通路，可以输出
                        for (int j = 0; j < 2; j++)
                            if (minTurns2[tx][ty][(id + 3 - j * 2) % 4] < 1000000) {
                                printResult(tx, ty, id, (id + 3 - j * 2) % 4);
                                return;
                            }
                    }

                }
            }
        }
        while (q2.front().turns <= level) {
            pos temp = q2.front();
            q2.pop();
            int x = temp.x;
            int y = temp.y;
            int dir = temp.direction;
            int turns = temp.turns;
            int tx = x;
            int ty = y;
            while (true) {
                tx -= dx[dir];
                ty -= dy[dir];
                if (maze[tx][ty] == '*')
                    break;
                for (int i = 0; i < 2; i++) {
                    // 处理技巧：i = 0时id = dir左拐，i = 1时id = dir右拐
                    // 因为方向从0到3分别是东南西北
                    // 每个方向左拐都是(它的数字-1) % 4对应的方向，因为有可能减成负数所以再加4，等于+3后%4，结果一样
                    // 而每个方向右拐，都是(它的数字+1) % 4对应的方向
                    int id = (dir + 3 - i * 2) % 4;
                    if (maze[tx - dx[id]][ty - dy[id]] == '.' && minTurns[tx][ty][id] > turns + 1) {
                        tail2 += 1;
                        pos tempnextpos;
                        tempnextpos.x = tx;
                        tempnextpos.y = ty;
                        tempnextpos.direction = id;
                        tempnextpos.turns = turns + 1;
                        q2.push(tempnextpos);

                        minTurns2[tx][ty][id] = turns + 1;
                        pre2[tx][ty][id][0] = x;
                        pre2[tx][ty][id][1] = y;
                        pre2[tx][ty][id][2] = dir;
                        // 如果遇到了反向来的相同状态，就意味着找到了一条通路，可以输出
                        for (int j = 0; j < 2; j++)
                            if (minTurns[tx][ty][(id + 3 - j * 2) % 4] < 1000000) {
                                printResult(tx, ty, (id + 3 - j * 2) % 4, id);
                                return;
                            }
                    }

                }
            }
        }
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

    double_bfs();

    cout << "Total States: " << tail + tail2 << endl;
    return 0;
}