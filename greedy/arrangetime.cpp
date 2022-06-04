//
// Created by 李汇川 on 2022/6/4.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Activity {
 public:
  int start;
  int end;
  Activity(int start, int end) {
    this->start = start;
    this->end = end;
  }
};

bool comp(Activity &a, Activity &b) {
  return a.end < b.end;
}

vector<bool> greedySelectActivity(vector<Activity> list) {
  int n = list.size();
  bool results[n];
  results[0] = true;
  int j = 0;
  for (int i = 1; i < n; i++) {
    if (list[i].start >= list[j].end) {
      // 被选中
      results[i] = true;
      j = i;
    } else {
      results[i] = false;
    }
  }
  vector<bool> r(results, results + n);
  return r;
}

int main() {
  vector<Activity> list;
  list.push_back(Activity(3, 5));
  list.push_back(Activity(1, 4));
  list.push_back(Activity(5, 7));
  list.push_back(Activity(0, 6));
  list.push_back(Activity(6, 10));
  list.push_back(Activity(3, 8));
  list.push_back(Activity(5, 9));
  list.push_back(Activity(8, 12));
  list.push_back(Activity(8, 11));
  list.push_back(Activity(2, 13));
  list.push_back(Activity(12, 14));
  // 按照结束时间排序
  sort(list.begin(), list.end(), comp);
  vector<bool> r = greedySelectActivity(list);
  cout << "被安排上的活动为：" << endl;
  for (int i = 0; i < list.size(); i++) {
    // 张数大于 0 才打印
    if (r[i]) {
      cout << "[" << list[i].start << ", " << list[i].end << "] " << endl;
    }
  }
  return 0;
}