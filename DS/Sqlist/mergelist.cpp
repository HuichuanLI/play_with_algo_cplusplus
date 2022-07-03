//
// Created by lhc456 on 2022/7/2.
//
#include<iostream>
#include"sqlite.h"//引入自定义头文件,源码目录下名为sqlist.h的文件

using namespace std;

void MergeSqlist(SqList La, SqList Lb, SqList &Lc)//顺序有序表的合并
{
    //已知顺序有序表La和Lb的元素按值非递减排列
    //La和Lb合并得到新的顺序有序表Lc，Lc的元素也按值非递减排列
    int i, j, k;
    i = j = k = 0;
    Lc.length = La.length + Lb.length; //新表长度为待合并两表的长度之和
    Lc.elem = new int[Lc.length]; //为合并后的新表分配一段空间
    while (i < La.length && j < Lb.length) //两个表都非空
    {
        if (La.elem[i] <= Lb.elem[j]) //依次取出两表中值较小放入到Lc表中
            Lc.elem[k++] = La.elem[i++];
        else
            Lc.elem[k++] = Lb.elem[j++];
    }
    while (i < La.length) //La有剩余，依次将La的剩余元素插入Lc表的最后
        Lc.elem[k++] = La.elem[i++];
    while (j < Lb.length) //Lb有剩余，依次将Lb的剩余元素插入Lc表的最后
        Lc.elem[k++] = Lb.elem[j++];
}

bool CreateList(SqList &L) //创建一个顺序表L
{   //L加&表示引用类型参数，函数内部的改变跳出函数仍然有效
    //不加&内部改变，跳出函数后无效
    int a, i = 1;
    cin >> a;
    while (a != -1) {
        ListInsert_Sq(L, i, a);
        cin >> a;
        i++;
    }
    return true;
}

void print(SqList L) {
    cout << "输出顺序表" << endl;
    for (int j = 0; j <= L.length - 1; j++)
        cout << L.elem[j] << "   ";
    cout << endl;
}

int main() {
    SqList La, Lb, Lc;
    cout << "创建有序(非递减)顺序表La:" << endl;
    InitList(La); //La表的创建
    CreateList(La); //依次往顺序表La里输入数据
    print(La);
    cout << "创建有序(非递减)顺序表Lb:" << endl;
    InitList(Lb); //Lb表的创建
    CreateList(Lb); //依次往顺序表Lb里输入数据
    print(Lb);
    MergeSqlist(La, Lb, Lc); //将顺序表La和Lb进行合并
    cout << "非递减线性表La，Lb合并后的非递减线性表lc为：\n"; //输出合并后的有序顺序表Lc
    print(Lc);
    cout << endl;
    return 0;
}
