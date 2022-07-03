//
// Created by lhc456 on 2022/7/3.
//
#include<iostream>
#include<algorithm>//abs()求绝对值函数需要此头文件

using namespace std;

typedef struct LNode {
    int data; //结点的数据域
    struct LNode *next; //结点的指针域
} LNode, *LinkList; //LinkList为指向结构体LNode的指针类型
int m, n;

bool InitList_L(LinkList &L)//构造一个空的单链表L
{
    L = new LNode;     //生成新结点作为头结点，用头指针L指向头结点
    if (!L)
        return false;  //生成结点失败
    L->next = NULL;   //头结点的指针域置空
    return true;
}

void CreateList_R(LinkList &L)//尾插法创建单链表
{
    //输入n个元素的值，建立带表头结点的单链表L
    LinkList s, r;
    L = new LNode;
    L->next = NULL; //先建立一个带头结点的空链表
    r = L; //尾指针r指向头结点
    cout << "请输入元素个数m,数据元素的范围n：" << endl;
    cin >> m >> n;
    cout << "输入m个绝对值不超过n的整数..." << endl;
    while (m--) {
        s = new LNode;//生成新结点
        cin >> s->data; //输入元素值赋给新结点的数据域
        s->next = NULL;
        r->next = s;//将新结点s插入尾结点r之后
        r = s;//r指向新的尾结点s
    }
}

void Deleterep(LinkList &L)//删除重复元素
{
    LinkList p, q;
    int x;
    int *flag = new int[n + 1]; //定义flag数组，分配n+1个空间
    for (int i = 0; i < n + 1; i++) //初始化
        flag[i] = 0;
    p = L; //指向头结点
    while (p->next != NULL) {
        x = abs(p->next->data);
        if (flag[x] == 0)//未出现过
        {
            flag[x] = 1; //标记出现
            p = p->next;           //指针后移
        } else {
            q = p->next;
            p->next = q->next;//删除重复元素
            delete q;

        }
    }
    delete[]flag;
}

void Listprint_L(LinkList L) //单链表的输出
{
    LinkList p;
    p = L->next;
    while (p) {
        cout << p->data << "\t";
        p = p->next;
    }
    cout << endl;
}

int main() {
    LinkList L;
    cout << "创建单链表L:" << endl;
    InitList_L(L);
    CreateList_R(L);
    cout << "单链表数据为：" << endl;
    Listprint_L(L);
    cout << "删除重复元素：" << endl;
    Deleterep(L);
    Listprint_L(L);
    return 0;
}
