//
// Created by lhc456 on 2022/6/25.
//
#include <iostream>
#include <queue>

bool infected[1001];
int graph[1001][1001];
int n, m, head, tail, tmp;
int step[1001];
using namespace std;

std::queue<int> q;


void bfs() {
    while (!q.empty()) {
        int state = q.front();
        q.pop();
        int stateStep = step[head++];
        for (int i = 1; i <= graph[state][0]; i += 1) {
            int tempState = graph[state][i];
            int tempStep = stateStep + 1;
            if (tempStep > 2)
                return;
            if (infected[tempState])
                continue;
            infected[tempState] = true;
            q.push(tempState);
            step[tempState] = tempStep;
        }
    }
}

int main() {

    memset(graph, 0, sizeof(graph));
    memset(infected, 0, sizeof(infected));
    memset(step, 0, sizeof(step));
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
        q.push(tmp);
    }

    bfs();

    for (int i = 1; i <= n; i++)
        if (infected[i])
            cout << i << endl;
    return 0;
}