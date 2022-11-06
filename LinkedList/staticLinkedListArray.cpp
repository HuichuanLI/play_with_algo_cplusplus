//
// Created by lhc456 on 2022/11/6.
//
#include <iostream>

const int N = 105;                       //定义静态链表的空间大小
struct node {                             //单向链表
    int id, nextid;                      //单向指针
    //int data;                            //如有必要，定义一个有意义的数据
} nodes[N];                               //定义在全局的静态分配
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    nodes[0].nextid = 1;
    for (int i = 1; i <= n; i++) {
        nodes[i].id = i;
        nodes[i].nextid = i + 1;
    }
    nodes[n].nextid = 1;                 //循环链表：尾指向头
    int now = 1, prev = 1;               //从第1个开始
    while ((n--) > 1) {
        for (int i = 1; i < m; i++) {
            prev = now;
            now = nodes[now].nextid;
        } //数到m停下
        printf("%d ", nodes[now].id);    //带空格打印
        nodes[prev].nextid = nodes[now].nextid;    //跳过结点now，即删除now
        now = nodes[prev].nextid;        //新的now
    }
    printf("%d", nodes[now].nextid);     //打印最后一个，后面不带空格
    return 0;
}