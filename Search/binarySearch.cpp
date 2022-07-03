//
// Created by lhc456 on 2022/7/3.
//
#include<iostream>
#include<cstdlib> //排序sort函数需要该头文件
#include<algorithm>
using namespace std;
const int M=100;
int x,n,i;
int s[M];

int BinarySearch(int s[],int n,int x)//二分查找非递归算法
{
    int low=0,high=n-1;  //low指向有序数组的第一个元素，high指向有序数组的最后一个元素
    while(low<=high)
    {
        int middle=(low+high)/2;  //middle为查找范围的中间值
        if(x==s[middle])  //x等于查找范围的中间值，算法结束
            return middle;
        else if(x>s[middle]) //x大于查找范围的中间元素，则从左半部分查找
            low=middle+1;
        else            //x小于查找范围的中间元素，则从右半部分查找
            high=middle-1;
    }
    return -1;
}

int recursionBS (int s[],int x,int low,int high) //二分查找递归算法
{
    //low指向数组的第一个元素，high指向数组的最后一个元素
    if(low>high)              //递归结束条件
        return -1;
    int middle=(low+high)/2;  //计算middle值(查找范围的中间值)
    if(x==s[middle])          //x等于s[middle]，查找成功，算法结束
        return middle;
    else if(x<s[middle])      //x小于s[middle]，则从前半部分查找
        return recursionBS (s,x,low,middle-1);
    else               //x大于s[middle]，则从后半部分查找
        return recursionBS (s,x,middle+1,high);
}

int main()
{
    cout<<"该数列中的元素个数n为：";
    cin>>n;
    cout<<"请依次输入数列中的元素：";
    for(i=0;i<n;i++)
        cin>>s[i];
    sort(s,s+n); //二分查找的序列必须是有序的，如果无序需要先排序
    cout<<"排序后的数组为：";
    for(i=0;i<n;i++)
        cout<<s[i]<<" ";
    cout<<endl;
    cout<<"请输入要查找的元素：";
    cin>>x;
    //i=BinarySearch(s,n,x);
    i=recursionBS(s,x,0,n-1);
    if(i==-1)
        cout<<"该数列中没有要查找的元素"<<endl;
    else
        cout<<"要查找的元素在第"<<i+1<<"位"<<endl;//位序和下标差1
    return 0;
}
