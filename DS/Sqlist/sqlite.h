//
// Created by lhc456 on 2022/7/2.
//

#ifndef DYNAMIC_ARRAY_SQLITE_H
#define DYNAMIC_ARRAY_SQLITE_H
#define  Maxsize 100  //最大空间

typedef struct {
    int *elem;
    int length;       // 顺序表的长度
} SqList;

bool InitList(SqList &L) //构造一个空的顺序表L
{   //L加&表示引用类型参数，函数内部的改变跳出函数仍然有效
//不加&内部改变，跳出函数后无效
    L.elem = new int[Maxsize];    //为顺序表分配Maxsize个空间
    if (!L.elem) return false;      //存储分配失败
    L.length = 0;                //空表长度为0
    return true;
}

//bool CreateList(SqList &L) //创建一个顺序表L
//{   //L加&表示引用类型参数，函数内部的改变跳出函数仍然有效
////不加&内部改变，跳出函数后无效
//    int a,i=0;
//    cin>>a;
//    while(a!=-1)
//    {
//     if(L.length==Maxsize)
//     {
//       cout<<"顺序表已满！";
//       return false;
//     }
//     L.elem[i++]=a;
//     L.length++;
//     cin>>a;
//   }
//   return true;
//}

bool GetElem(SqList L, int i, int &e) {
    if (i < 1 || i > L.length) return false;
    //判断i值是否合理，若不合理，返回false
    e = L.elem[i - 1];   //第i-1的单元存储着第i个数据
    return true;
}

int LocateELem(SqList L, int x) {
    for (int i = 0; i < L.length; i++)
        if (L.elem[i] == x) return i + 1; //第几个元素，例如第5个元素，下标其实为4
    return -1;
}

bool ListInsert_Sq(SqList &L, int i, int e) {
    if (i < 1 || i > L.length + 1) return false;     //i值不合法
    if (L.length == Maxsize) return false; //存储空间已满
    for (int j = L.length - 1; j >= i - 1; j--)
        L.elem[j + 1] = L.elem[j];   //从最后一个元素开始后移，直到第i个元素后移
    L.elem[i - 1] = e;              //将新元素e放入第i个位置
    L.length++;                //表长增1
    return true;
}

bool ListDelete_Sq(SqList &L, int i, int &e) {
    if ((i < 1) || (i > L.length)) return false;     //i值不合法
    e = L.elem[i - 1];   //将欲删除的元素保留在e中
    for (int j = i; j <= L.length - 1; j++)
        L.elem[j - 1] = L.elem[j]; //被删除元素之后的元素前移
    L.length--; //表长减1
    return true;
}

//void print(SqList L)
//{
//   cout << "输出顺序表" << endl;
//   for(int j=0;j<=L.length-1;j++)
//     cout<<L.elem[j]<<"   ";
//   cout<<endl;
//}

void DestroyList(SqList &L) {
    if (L.elem) delete[]L.elem;    //释放存储空间
}


#endif //DYNAMIC_ARRAY_SQLITE_H
