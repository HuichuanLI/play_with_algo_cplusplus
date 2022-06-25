//
// Created by lhc456 on 2022/6/26.
//
#include<iostream>
using namespace std;

int n, m, step;
bool graph[100][100], hashOption[100][100];
bool hashState[100];
int node[100];

void dfs(int k) {
    for (int i = 0; i < n; i++)
        if (hashOption[k][i]) {
            if (hashState[i])
                continue;
            hashState[i] = true;
            hashOption[k][i] = false;
            hashOption[i][k] = false;
            node[++step] = i;
            dfs(i);
        }
}

void dfs_init() {
    memset(hashState, 0, sizeof(hashState));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (graph[i][j])
                hashOption[i][j] = true;
    step = 0;
    node[0] = 0;
    hashState[0] = true;
    dfs(1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    memset(graph, 0, sizeof(graph));
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        graph[x][y] = true;
        graph[y][x] = true;
    }

    dfs_init();

    for (int i = 0; i < n; i++)
        cout << node[i] << " ";
    return 0;
}