//
// Created by lhc456 on 2023/4/15.
//
#include <iostream>

#pragma warning (disable: 4996)
using namespace std;

//单链表中每个节点的定义
template<typename T> //T代表数据元素的类型
struct Node {
    T data;    //数据域，存放数据元素
    Node<T> *next;  //指针域，指向下一个同类型（和本节点类型相同）节点
};

//单链表的定义
template<typename T>
class LinkList {
public:
    LinkList();      //构造函数
    ~LinkList()/*{}*/;     //析构函数

public:
    bool ListInsert(int i, const T &e);  //在第i个位置插入指定元素e
    bool ListDelete(int i);              //删除第i个位置的元素

    bool GetElem(int i, T &e);           //获得第i个位置的元素值
    int LocateElem(const T &e);         //按元素值查找其在单链表中第一次出现的位置

    void DispList();                     //输出单链表中的所有元素
    int ListLength();                   //获取单链表的长度
    bool Empty();                        //判断单链表是否为空
    void ReverseList();                  //翻转单链表


private:
    Node<T> *m_head; //头指针（指向链表第一个节点的指针，如果链表有头结点则指向头结点）
    int m_length;    //单链表当前长度（当前有几个元素），为编写程序更加方便和提高程序运行效率而引入，但不是必须引入
};

//通过构造函数对单链表进行初始化
template<typename T>
LinkList<T>::LinkList() {
    m_head = new Node<T>; //先创建一个头结点
    m_head->next = nullptr;
    m_length = 0;  //头结点不计入单链表的长度
}

//在第i个位置（位置编号从1开始）插入指定元素e
template<typename T>
bool LinkList<T>::ListInsert(int i, const T &e) {
    if (i < 1 || i > (m_length + 1)) {
        cout << "元素" << e << "插入的位置" << i << "不合法，合法的位置是1到" << m_length + 1 << "之间!" << endl;
        return false;
    }
    Node<T> *p_curr = m_head;
    //整个for循环用于找到第i-1个节点
    for (int j = 0; j < (i - 1); ++j) //j从0开始，表示p_curr刚开始指向的是第0个节点（头结点）
    {
        p_curr = p_curr->next; //pcurr会找到当前要插入的位置，比如要在第2个位置插入，pcurr会指向第1个位置
    }
    Node<T> *node = new Node<T>;
    node->data = e;
    node->next = p_curr->next;//让新节点链上后续链表，因为pcurr->next指向后续的链表节点
    p_curr->next = node;//让当前位置链上新节点，因为node指向新节点

    cout << "成功在位置为" << i << "处插入元素" << e << "!" << endl;
    m_length++;            //实际表长+1
    return true;

}

//删除第i个位置的元素
template<typename T>
bool LinkList<T>::ListDelete(int i) {

    if (m_length < 1) {
        cout << "当前单链表为空，不能删除任何数据!" << endl;
        return false;
    }
    if (i < 1 || i > m_length) {
        cout << "删除的位置" << i << "不合法，合法的位置是1到" << m_length << "之间!" << endl;
        return false;
    }

    Node<T> *p_curr = m_head;

    //整个for循环用于找到第i-1个节点
    for (int j = 0; j < (i - 1); ++j)//j从0开始，表示p_curr刚开始指向的是第0个节点（头结点）
    {
        p_curr = p_curr->next; //pcurr会找到当前要删除的位置所代表的节点的前一个节点的位置，比如要删除第2个位置的节点，pcurr会指向第1个位置(节点)
    }
    Node<T> *p_willdel = p_curr->next; //p_willdel指向待删除的节点
    p_curr->next = p_willdel->next; //第i-1个节点的next指针指向第i+1个节点
    cout << "成功删除位置为" << i << "的元素，该元素的值为" << p_willdel->data << "!" << endl;
    m_length--;       //实际表长-1
    delete p_willdel;
    return true;
}


//获得第i个位置的元素值
template<class T>
bool LinkList<T>::GetElem(int i, T &e) {
    if (m_length < 1) {
        cout << "当前单链表为空，不能获取任何数据!" << endl;
        return false;
    }

    if (i < 1 || i > m_length) {
        cout << "获取元素的位置" << i << "不合法，合法的位置是1到" << m_length << "之间!" << endl;
        return false;
    }

    Node<T> *p_curr = m_head;
    for (int j = 0; j < i; ++j) {
        p_curr = p_curr->next;
    }
    e = p_curr->data;
    cout << "成功获取位置为" << i << "的元素，该元素的值为" << e << "!" << endl;
    return true;
}

//按元素值查找其在单链表中第一次出现的位置
template<class T>
int LinkList<T>::LocateElem(const T &e) {
    Node<T> *p_curr = m_head;
    for (int i = 1; i <= m_length; ++i) {
        if (p_curr->next->data == e) {
            cout << "值为" << e << "的元素在单链表中第一次出现的位置为" << i << "!" << endl;
            return i;
        }
        p_curr = p_curr->next;
    }
    cout << "值为" << e << "的元素在单链表中没有找到!" << endl;
    return -1;  //返回-1表示查找失败
}


//输出单链表中的所有元素，时间复杂度为O(n)
template<class T>
void LinkList<T>::DispList() {
    Node<T> *p = m_head->next;
    while (p != nullptr) //这里采用while循环或者for循环书写都可以
    {
        cout << p->data << " ";  //每个数据之间以空格分隔
        p = p->next;
    }
    cout << endl; //换行
}


//获取单链表的长度，时间复杂度为O(1)
template<class T>
int LinkList<T>::ListLength() {
    return m_length;
}


//判断单链表是否为空，时间复杂度为O(1)
template<class T>
bool LinkList<T>::Empty() {
    if (m_head->next == nullptr) //单链表为空（如果是不带头结点的单链表则用if(m_head == nullptr）来判断是否为空）
    {
        return true;
    }
    return false;
}


//翻转单链表，时间复杂度为O(n)
template<typename T>
void LinkList<T>::ReverseList() {
    if (m_length <= 1) {
        //如果顺序表中没有元素或者只有一个元素，那么就不用做任何操作
        return;
    }

    //至少有两个节点才会走到这里
    Node<T> *pothersjd = m_head->next->next;   //指向从第二个节点开始的后续节点
    m_head->next->next = nullptr;              //第一个节点的指针域先置空

    Node<T> *ptmp;
    while (pothersjd != nullptr) {
        //比如a1、a2、a3、a4共4个节点，第一次执行该循环时的指向看下面代码中的注释
        ptmp = pothersjd;               //ptmp代表a2
        pothersjd = pothersjd->next;    //现在pothersjd指向a3

        ptmp->next = m_head->next;      //a2指向a1
        m_head->next = ptmp;            //头结点指向a2
    }
}

//通过析构函数对单链表进行资源释放，时间复杂度为O(n)
template<typename T>
LinkList<T>::~LinkList() {
    Node<T> *pnode = m_head->next;
    Node<T> *ptmp;
    while (pnode != nullptr) //该循环负责释放数据节点
    {
        ptmp = pnode;
        pnode = pnode->next;

        delete ptmp;
    }
    delete m_head;    //释放头结点
    m_head = nullptr; //非必须
    m_length = 0;     //非必须
}


int main() {

    LinkList<int> slinkobj;

    slinkobj.ListInsert(1, 12);
    slinkobj.ListInsert(1, 24);
    slinkobj.ListInsert(3, 48);
    slinkobj.ListInsert(2, 100);

    slinkobj.ListDelete(4);

    int eval = 0;
    slinkobj.GetElem(3, eval);//如果GetElem()返回true，则eval中保存着获取到的元素值

    int findvalue = 100; //在单链表中要找的元素值
    slinkobj.LocateElem(findvalue);

    slinkobj.DispList();
    slinkobj.ReverseList();
    slinkobj.DispList();

    return 0;
}