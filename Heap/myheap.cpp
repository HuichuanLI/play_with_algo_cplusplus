//
// Created by lhc456 on 2022/11/6.
//
#include<iostream>

using namespace std;
const int N = 1e6 + 5;
int heap[N], len = 0;                 //len记录当前二叉树的长度
void push(int x) {                  //上浮，插入新元素
    heap[++len] = x;
    int i = len;
    while (i > 1 && heap[i] < heap[i / 2]) {
        swap(heap[i], heap[i / 2]);
        i = i / 2;
    }
}

void pop() {                         //下沉，删除堆头，调整堆
    heap[1] = heap[len--];           //根结点替换为最后一个结点，然后结点数量减1
    int i = 1;
    while (2 * i <= len) {            //至少有左儿子
        int son = 2 * i;                //左儿子
        if (son < len && heap[son + 1] < heap[son])
            son++;                    //son<len表示有右儿子，选儿子中较小的
        if (heap[son] < heap[i]) {                   //与小的儿子交换
            swap(heap[son], heap[i]);
            i = son;                 //下沉到儿子处
        } else break;                  //如果不比儿子小，就停止下沉
    }
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int x;
            scanf("%d", &x);
            push(x);
        }  //加入堆
        else if (op == 2) printf("%d\n", heap[1]);        //打印堆头
        else pop();                                        //删除堆头
    }
    return 0;
}
