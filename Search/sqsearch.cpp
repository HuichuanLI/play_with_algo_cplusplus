//
// Created by lhc456 on 2022/7/3.
//
#include<iostream>

using namespace std;
#define Maxsize 100

int SqSearch(int r[], int n, int x)//顺序查找
{
    for (int i = 0; i < n; i++) //要判断i是否超过范围n
        if (r[i] == x) //r[i]和x比较
            return i;//返回下标
    return -1;
}

int SqSearch2(int r2[], int n, int x)//顺序查找优化算法
{
    int i;
    r2[0] = x;//待查找元素放入r[0]，作为监视哨
    for (i = n; r2[i] != x; i--);//不需要判断i是否超过范围
    return i;
}

int main() {
    int i, n, x, r[Maxsize], r2[Maxsize + 1];
    cout << "请输入元素个数n为：" << endl;
    cin >> n;
    cout << "请依次n个元素：" << endl;
    for (int i = 0; i < n; i++) {
        cin >> r[i];
        r2[i + 1] = r[i];//r2[]数组0空间未用，做监视哨
    }
    cout << endl;
    cout << "请输入要查找的元素：";
    cin >> x;
    //i=SqSearch(r,n,x);
//    if(i==-1)
//      cout<<"该数列中没有要查找的元素"<<endl;
//    else
//      cout<<"要查找的元素在第"<<i+1<<"位"<<endl;
    i = SqSearch2(r2, n, x);
    if (i == 0)
        cout << "该数列中没有要查找的元素" << endl;
    else
        cout << "要查找的元素在第" << i << "位" << endl;
    return 0;
}
