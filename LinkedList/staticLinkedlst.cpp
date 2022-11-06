//
// Created by lhc456 on 2022/11/6.
//
#include <iostream>
struct node{                            //定义链表结点
    int data;                           //结点的值
    node *next;                         //单向链表，只有一个next指针
};
int main(){
    int n,m;   scanf("%d %d",&n,&m);
    node *head,*p,*now,*prev;           //定义变量
    head = new node; head->data = 1; head->next=NULL; //分配第一个结点，数据置为1
    now = head;                         //当前指针是头
    for(int i=2;i<=n;i++){
        p = new node;  p->data = i; p->next = NULL;  //p是新结点
        now->next = p;                  //把申请的新结点连到前面的链表上
        now = p;                        //尾指针后移一个
    }
    now->next = head;                   //尾指针指向头：循环链表建立完成
//以上是建立链表，下面是本题的逻辑和流程。后面4种代码，逻辑流程完全一致。
    now = head, prev = head;            //从第1个开始数
    while((n--) >1 ){
        for(int i=1;i<m;i++){           //数到m，停下
            prev = now;                 //记录上一个位置，用于下面跳过第m个结点
            now = now->next;
        }
        printf("%d ", now->data);       //输出第m结点，带空格
        prev->next = now->next;         //跳过这个结点
        delete now;                     //释放结点
        now = prev->next;               //新的一轮
    }
    printf("%d", now->data);            //打印最后一个，后面不带空格
    delete now;                         //释放最后一个结点
    return 0;
}