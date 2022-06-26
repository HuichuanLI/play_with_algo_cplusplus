//
// Created by lhc456 on 2022/6/26.
//
#include<iostream>
#include <fstream>

using namespace std;

const int n = 40;
const int k = 300;

int main() {
    ios::sync_with_stdio(false);
    ofstream fout("/Users/lhc456/Desktop/c++/play_with_algo_cplusplus/Search/searchadavnced/data/4.in");

    char maze[102][102];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            maze[i][j] = '.';

    for (int i = 0; i <= n + 1; i++) {
        maze[0][i] = '*';
        maze[i][0] = '*';
        maze[n + 1][i] = '*';
        maze[i][n + 1] = '*';
    }

    srand((unsigned) time(NULL));
    for (int i = 0; i < k; i++) {
        int x = rand() % (n + 1) + 1;
        int y = rand() % (n + 1) + 1;
        maze[x][y] = '*';
    }

    fout << n << endl;
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= n + 1; j++)
            fout << maze[i][j];
        fout << endl;
    }

    fout.close();
    return 0;
}