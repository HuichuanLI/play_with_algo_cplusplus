//
// Created by lhc456 on 2022/9/13.
//
#include <iostream>
#include <sys/time.h>                // for gettimeofday()

#include <fstream>

using namespace std;

int heap[10000001];
int n;

// 取系统时间，精确到毫秒
long getTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void shiftUp(int i) {
    // 假设是小根堆
    while (i > 0) {
        int j = (i - 1) / 2;    // 设置一个临时变量j来存储i的父节点标号
        if (heap[j] <= heap[i])    // 如果父节点小于等于该节点，直接退出循环
            break;
        int tmp = heap[i];
        heap[i] = heap[j];
        heap[j] = tmp;
        i = j;    // 不要忘记交换下标，否则会死循环！
    }
}

void shiftDown(int i) {
    // 假设是小根堆
    while (i * 2 + 1 < n) {  // 节点i至少需要包含一个叶节点
        int j = i * 2 + 1;   // 设置一个临时变量j来存储i可能需要交换的儿子的标号，初识为左子节点
        if (j < n - 1 && heap[j + 1] < heap[j])     // 代表j存在右兄弟节点，且右兄弟节点的值更小
            j++;
        if (heap[j] < heap[i]) {    // 如果子节点中较小的那一个小于父节点，则父子交换
            int tmp = heap[i];
            heap[i] = heap[j];
            heap[j] = tmp;
            i = j;    // 下标一定不要忘记交换！！
        } else     // 否则就可以跳出循环了，因为两个子节点都大于等于父节点了
            break;
    }
}

void buildHeap(int n) {
    for (int i = (n - 2) / 2; i >= 0; i--) {
        shiftDown(i);
    }
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
    if (n == 0) // 如果堆已经为空则返回
        return;
    shiftDown(0);
}

int main() {
    ios::sync_with_stdio(false);
    ifstream fin("1.in");
    ofstream fout("1.out");
    int tstart, tend;

    tstart = getTime();
    fin >> n;
    for (int i = 0; i < n; i++)
        fin >> heap[i];
    fin.close();
    tend = getTime();
    cout << "Read time:" << (tend - tstart + 0.0) / 1000 << endl;

    tstart = getTime();
    buildHeap(n);
    while (n > 0) {
        fout << heapGet() << ' ';
        heapDelete();
    }
    tend = getTime();
    cout << "Sorting time:" << (tend - tstart + 0.0) / 1000 << endl;

    fout.close();
    return 0;
}