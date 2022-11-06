//
// Created by lhc456 on 2022/11/6.
//
#include <iostream>
#include <list>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    list<int> node;
    for (int i = 1; i <= n; i++) node.push_back(i);   //建立链表
    list<int>::iterator it = node.begin();
    while (node.size() > 1) {                      //list的大小由STL自己管理
        for (int i = 1; i < m; i++) {                  //数到m
            it++;
            if (it == node.end())
                it = node.begin();  //循环：到末尾了再回头
        }
        cout << *it << " ";
        list<int>::iterator next = ++it;
        if (next == node.end()) next = node.begin();  //循环链表
        node.erase(--it);                         //删除这个结点，node.size()自动减1
        it = next;
    }
    cout << *it;
    return 0;
}