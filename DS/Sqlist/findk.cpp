#include<iostream>

using namespace std;

typedef struct LNode {
    int data; //结点的数据域
    struct LNode *next; //结点的指针域
} LNode, *LinkList; //LinkList为指向结构体LNode的指针类型

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
    int n;
    LinkList s, r;
    L = new LNode;
    L->next = NULL; //先建立一个带头结点的空链表
    r = L; //尾指针r指向头结点
    cout << "请输入元素个数n：" << endl;
    cin >> n;
    cout << "尾插法（正序）创建单链表..." << endl;
    while (n--) {
        s = new LNode;//生成新结点
        cin >> s->data; //输入元素值赋给新结点的数据域
        s->next = NULL;
        r->next = s;//将新结点s插入尾结点r之后
        r = s;//r指向新的尾结点s
    }
}

LinkList findk(LinkList L, int k) {
    LinkList p, q;
    p = L->next; //p为快指针，初始时指向第一个数据结点
    q = L->next; //q为慢指针，初始时指向第一个数据结点
    while (p->next != NULL) {
        if (--k <= 0)
            q = q->next;//q为慢指针
        p = p->next; //p为快指针；
    }
    if (k > 0)
        return NULL;
    else
        return q;//返回中间结点指针
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
    LinkList L, r;
    int k;
    cout << "创建单链表L:" << endl;
    InitList_L(L);
    CreateList_R(L);
    cout << "单链表数据为：" << endl;
    Listprint_L(L);
    cout << "需要查找倒数第k个结点的k值：" << endl;
    cin >> k;
    r = findk(L, k);
    if (r)
        cout << "单链表倒数第" << k << "个结点数据为：" << r->data << endl;
    else
        cout << "没找到倒数第" << k << "个结点!" << endl;
    return 0;
}
