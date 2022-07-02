//
// Created by lhc456 on 2022/7/2.
//
#include<iostream>

using namespace std;

#define  Maxsize 100  //最大空间

class SqList {
public:
    bool InitList(SqList &L) //构造一个空的顺序表L
    {   //L加&表示引用类型参数，函数内部的改变跳出函数仍然有效
//不加&内部改变，跳出函数后无效
        L.elem = new int[Maxsize];    //为顺序表分配Maxsize个空间
        if (!L.elem) return false;      //存储分配失败
        L.length = 0;                //空表长度为0
        return true;
    }

    bool CreateList(SqList &L) //创建一个顺序表L
    {   //L加&表示引用类型参数，函数内部的改变跳出函数仍然有效
        //不加&内部改变，跳出函数后无效
        int a, i = 0;
        cin >> a;
        while (a != -1) {
            if (L.length == Maxsize) {
                cout << "顺序表已满！";
                return false;
            }
            L.elem[i++] = a;
            L.length++;
            cin >> a;
        }
        return true;
    }

    bool GetElem(SqList L, int i, int &e) {
        if (i < 1 || i > L.length) return false;
        //判断i值是否合理，若不合理，返回false
        e = L.elem[i - 1];   //第i-1的单元存储着第i个数据
        return true;
    }

    int LocateELem(SqList L, int x) {
        for (int i = 0; i < L.length; i++)
            if (L.elem[i] == x)
                return i + 1; //第几个元素，例如第5个元素，下标其实为4
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

    void print(SqList L) {
        cout << "输出顺序表" << endl;
        for (int j = 0; j <= L.length - 1; j++)
            cout << L.elem[j] << "   ";
        cout << endl;
    }

    void DestroyList(SqList &L) {
        if (L.elem) delete[]L.elem;    //释放存储空间
    }

public:
    int *elem;
    int length; // 顺序表的长度
};


int main() {
    SqList myL;
    int i, e, x;
    cout << "1. 初始化\n";
    cout << "2. 创建\n";
    cout << "3. 取值\n";
    cout << "4. 查找\n";
    cout << "5. 插入\n";
    cout << "6. 删除\n";
    cout << "7. 输出\n";
    cout << "8. 销毁\n";
    cout << "0. 退出\n";
    int choose = -1;
    while (choose != 0) {
        cout << "请选择:";
        cin >> choose;
        switch (choose) {
            case 1://初始化顺序表
                cout << "顺序表初始化..." << endl;
                if (myL.InitList(myL))
                    cout << "顺序表初始化成功！" << endl;
                else
                    cout << "顺序表初始化失败！" << endl;
                break;
            case 2://创建顺序表
                cout << "顺序表创建..." << endl;
                cout << "输入整型数，输入-1结束" << endl;
                if (myL.CreateList(myL))
                    cout << "顺序表创建成功！" << endl;
                else
                    cout << "顺序表创建失败！" << endl;
                break;
            case 3://取值
                cout << "输入整型数i，取第i个元素输出" << endl;
                cin >> i;
                if (myL.GetElem(myL, i, e))
                    cout << "第i个元素是： " << e << endl;
                else
                    cout << "顺序表取值失败！" << endl;;
                cout << "第i个元素是： " << e << endl;
                break;
            case 4://查找
                cout << "请输入要查找的数x:";
                cin >> x;
                if (myL.LocateELem(myL, x) == -1)
                    cout << "查找失败！" << endl;
                else
                    cout << "查找成功！" << endl;
                break;
            case 5://插入
                cout << "请输入要插入的位置和要插入的数据元素e:";
                cin >> i >> e;
                if (myL.ListInsert_Sq(myL, i, e))
                    cout << "插入成功！" << endl;
                else
                    cout << "插入失败！" << endl;
                break;
            case 6://删除
                cout << "请输入要删除的位置i:";
                cin >> i;
                if (myL.ListDelete_Sq(myL, i, e))
                    cout << " 删除成功！" << endl;
                else
                    cout << "删除失败！" << endl;
                break;
            case 7://输出
                myL.print(myL);
                break;
            case 8://销毁
                cout << "顺序表销毁..." << endl;
                myL.DestroyList(myL);
                break;
        }
    }
    return 0;
}
