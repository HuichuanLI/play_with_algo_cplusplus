//
// Created by lhc456 on 2023/4/15.
//
#include <iostream>

#pragma warning (disable: 4996)
using namespace std;


//双链表中每个节点的定义
template<typename T> //T代表数据元素的类型
struct DblNode {
    T data;  //数据域，存放数据元素
    DblNode<T> *prior; //前趋指针，指向前一个同类型（和本节点类型相同）节点
    DblNode<T> *next;  //后继指针，指向下一个同类型（和本节点类型相同）节点
};


//双链表的定义
template<typename T>
class DblLinkList {
public:
    DblLinkList();      //构造函数
    ~DblLinkList();     //析构函数

public:
    bool ListInsert(int i, const T &e);  //在第i个位置插入指定元素e
    bool ListDelete(int i);              //删除第i个位置的元素

    bool GetElem(int i, T &e);           //获得第i个位置的元素值
    int LocateElem(const T &e);         //按元素值查找其在双链表中第一次出现的位置

    void DispList();                     //输出双链表中的所有元素
    int ListLength();                   //获取双链表的长度
    bool Empty();                        //判断双链表是否为空

private:
    DblNode<T> *m_head; //头指针（指向链表第一个节点的指针，如果链表有头结点则指向头结点）
    int m_length;    //双链表当前长度（当前有几个元素），为编写程序更加方便和提高程序运行效率而引入，但不是必须引入
};

//通过构造函数对双链表进行初始化
template<typename T>
DblLinkList<T>::DblLinkList() {
    m_head = new DblNode<T>; //先创建一个头结点
    m_head->next = nullptr; //该值暂时为nullptr，因为还没有后继节点
    m_head->prior = nullptr; //该值一直为nullptr
    m_length = 0;  //头结点不计入双链表的长度
}


//通过析构函数对双链表进行资源释放
template<typename T>
DblLinkList<T>::~DblLinkList() {
    DblNode<T> *pnode = m_head->next;
    DblNode<T> *ptmp;
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


//在第i个位置（位置编号从1开始）插入指定元素e
template<typename T>
bool DblLinkList<T>::ListInsert(int i, const T &e) {
    //判断插入位置i是否合法，i的合法值应该是1到length+1之间
    if (i < 1 || i > (m_length + 1)) {
        cout << "元素" << e << "插入的位置" << i << "不合法，合法的位置是1到" << m_length + 1 << "之间!" << endl;
        return false;
    }
    DblNode<T> *p_curr = m_head;

    //整个for循环用于找到第i-1个节点
    for (int j = 0; j < (i - 1); ++j)//j从0开始，表示p_curr刚开始指向的是第0个节点（头结点）
    {
        p_curr = p_curr->next; //pcurr会找到当前要插入的位置，比如要在第2个位置插入，pcurr会指向第1个位置(节点)
    }

    DblNode<T> *node = new DblNode<T>;
    node->data = e;
    node->next = p_curr->next;//让新节点链上后续链表，因为pcurr->next指向后续的链表节点
    node->prior = p_curr;

    if (p_curr->next != nullptr)
        p_curr->next->prior = node;

    p_curr->next = node;//让当前位置链上新节点，因为node指向新节点

    cout << "成功在位置为" << i << "处插入元素" << e << "!" << endl;
    m_length++;            //实际表长+1
    return true;

}

//输出双链表中的所有元素，时间复杂度为O(n)
template<class T>
void DblLinkList<T>::DispList() {
    DblNode<T> *p = m_head->next;
    while (p != nullptr) //这里采用while循环或者for循环书写都可以
    {
        cout << p->data << " ";  //每个数据之间以空格分隔
        p = p->next;
    }
    cout << endl; //换行
}


//删除第i个位置的元素
template<typename T>
bool DblLinkList<T>::ListDelete(int i) {
    if (m_length < 1) {
        cout << "当前双链表为空，不能删除任何数据!" << endl;
        return false;
    }
    if (i < 1 || i > m_length) {
        cout << "删除的位置" << i << "不合法，合法的位置是1到" << m_length << "之间!" << endl;
        return false;
    }

    DblNode<T> *p_curr = m_head;


    //整个for循环用于找到第i-1个节点
    for (int j = 0; j < (i - 1); ++j)//j从0开始，表示p_curr刚开始指向的是第0个节点（头结点）
    {
        p_curr = p_curr->next; //pcurr会找到当前要删除的位置所代表的节点的前一个节点的位置，比如要删除第2个位置的节点，pcurr会指向第1个位置(节点)
    }

    DblNode<T> *p_willdel = p_curr->next; //p_willdel指向待删除的节点
    DblNode<T> *p_willdelNext = p_willdel->next; //p_willdelNext指向待删除节点的下一个节点
    p_curr->next = p_willdel->next; //第i-1个节点的next指针指向第i+1个节点
    if (p_willdelNext != nullptr)
        p_willdelNext->prior = p_curr;//第i+1个节点的prior指针指向第i-1个节点

    cout << "成功删除位置为" << i << "的元素，该元素的值为" << p_willdel->data << "!" << endl;
    m_length--;       //实际表长-1
    delete p_willdel;
    return true;
}

//获得第i个位置的元素值
template<class T>
bool DblLinkList<T>::GetElem(int i, T &e) {
    if (m_length < 1) {
        cout << "当前双链表为空，不能获取任何数据!" << endl;
        return false;
    }

    if (i < 1 || i > m_length) {
        cout << "获取元素的位置" << i << "不合法，合法的位置是1到" << m_length << "之间!" << endl;
        return false;
    }

    DblNode<T> *p_curr = m_head;
    for (int j = 0; j < i; ++j) {
        p_curr = p_curr->next;
    }
    e = p_curr->data;
    cout << "成功获取位置为" << i << "的元素，该元素的值为" << e << "!" << endl;
    return true;
}


//按元素值查找其在双链表中第一次出现的位置

template<class T>
int DblLinkList<T>::LocateElem(const T &e) {
    DblNode<T> *p_curr = m_head;
    for (int i = 1; i <= m_length; ++i) {
        if (p_curr->next->data == e) {
            cout << "值为" << e << "的元素在双链表中第一次出现的位置为" << i << "!" << endl;
            return i;
        }
        p_curr = p_curr->next;
    }
    cout << "值为" << e << "的元素在双链表中没有找到!" << endl;
    return -1;  //返回-1表示查找失败
}

//获取双链表的长度，时间复杂度为O(1)
template<class T>
int DblLinkList<T>::ListLength() {
    return m_length;
}

//判断双链表是否为空，时间复杂度为O(1)
template<class T>
bool DblLinkList<T>::Empty() {
    if (m_head->next == nullptr) //双链表为空（如果是不带头结点的双链表则用if(m_head == nullptr）来判断是否为空）
    {
        return true;
    }
    return false;
}

int main() {

    DblLinkList<int> sdbllinkobj;

    sdbllinkobj.ListInsert(1, 12);
    sdbllinkobj.ListInsert(1, 24);
    sdbllinkobj.ListInsert(3, 48);
    sdbllinkobj.ListInsert(2, 100);
    sdbllinkobj.DispList();

    sdbllinkobj.ListDelete(4);
    sdbllinkobj.ListDelete(2);
    sdbllinkobj.DispList();

    return 0;
}