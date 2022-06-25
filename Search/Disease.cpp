//
// Created by lhc456 on 2022/6/25.
//
#include<iostream>

using namespace std;

int q[1001];
bool infected[1001];
int graph[1001][1001];
int n, m, head, tail, tmp;

void bfs() {
    while (head <= tail) {
        int state = q[head++];
        for (int i = 1; i <= graph[state][0]; i++) {
            int tempState = graph[state][i];
            if (infected[tempState])
                continue;
            infected[tempState] = true;
            q[++tail] = tempState;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    memset(graph, 0, sizeof(graph));
    memset(infected, 0, sizeof(infected));
    memset(q, 0, sizeof(q));
    head = 0;
    tail = -1;

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> graph[i][0];
        for (int j = 1; j <= graph[i][0]; j++)
            cin >> graph[i][j];
    }
    for (int i = 0; i < m; i++) {
        cin >> tmp;
        infected[tmp] = true;
        q[++tail] = tmp;
    }

    bfs();

    for (int i = 1; i <= n; i++)
        if (infected[i])
            cout << i << endl;
    return 0;
}