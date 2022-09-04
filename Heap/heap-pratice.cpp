//
// Created by lhc456 on 2022/9/4.
//
#include <iostream>

using namespace std;

int heap[100000001];
int n;


void shiftUp(int i) {
    while (i > 0) {
        int j = (i - 1) / 2;
        if (heap[j] <= heap[i]) {
            break;
        }
        int tmp = heap[i];
        heap[i] = heap[j];
        heap[j] = tmp;
        i = j;
    }
}

void shiftDown(int i) {
    while (i * 2 + 1 < n) {
        int j = i * 2 + 1;
        while (j < n - 1 && heap[j + 1] < heap[j])
            j++;
        if (heap[j] >= heap[i])
            break;
        int tmp = heap[i];
        heap[i] = heap[j];
        heap[j] = tmp;
        i = j;
    }
}

void buildHeap(int n) {
    for (int i = (n - 2) / 2; i >= 0; i--)
        shiftDown(i);
}

void heapInsert(int number) {
    heap[n++] = number;
    shiftUp(n - 1);
}

int heapGet() {
    return heap[0];
}

void heapDelete() {
    heap[0] = heap[--n];
    heap[n] = -INT_MAX;
    if (n == 0)
        return;
    shiftDown(0);
}

int main() {

    ifstream fin("data/1.in");
    ofstream fout("data/1.out");
}