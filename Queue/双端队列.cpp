//
// Created by lhc456 on 2022/11/6.
//
#include<iostream>
#include <deque>


using namespace std;
const int N = 1000005;
int a[N];
deque<int> q;                   //队列中的数据，实际上是元素在原序列中的位置
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++) {                       //输出最小值
        while (!q.empty() && a[q.back()] > a[i]) q.pop_back();   //去尾
        q.push_back(i);
        if (i >= m) {      //每个窗口输出一次
            while (!q.empty() && q.front() <= i - m) q.pop_front();  //删头
            printf("%d ", a[q.front()]);
        }
    }
    printf("\n");
    while (!q.empty()) q.pop_front();            //清空，下面再用一次
    for (int i = 1; i <= n; i++) {                       //输出最大值
        while (!q.empty() && a[q.back()] < a[i]) q.pop_back();   //去尾
        q.push_back(i);
        if (i >= m) {
            while (!q.empty() && q.front() <= i - m) q.pop_front();  //删头
            printf("%d ", a[q.front()]);
        }
    }
    printf("\n");
    return 0;
}