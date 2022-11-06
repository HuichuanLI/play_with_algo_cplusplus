//
// Created by lhc456 on 2022/11/6.
//
#include<iostream>

using namespace std;
const int INF = 0x7fffffff;

int main() {
    int t;
    cin >> t;              //测试用例个数
    for (int i = 1; i <= t; i++) {
        int n;
        cin >> n;
        int maxsum = -INF;         //最大子序和，初始化为一个极小负数
        int start = 1, end = 1, p = 1;   //起点，终点，扫描位置
        int sum = 0;               //子序和
        for (int j = 1; j <= n; j++) {
            int a;
            cin >> a;
            sum += a;     //读入一个元素，累加
            if (sum > maxsum) {
                maxsum = sum;
                start = p;
                end = j;
            }
            if (sum < 0) { //扫到j时，若前面的最大子序和是负数，从下一个重新开始求和
                sum = 0;
                p = j + 1;
            }
        }
        printf("Case %d:\n", i);
        printf("%d %d %d\n", maxsum, start, end);
        if (i != t) cout << endl;
    }
    return 0;
}