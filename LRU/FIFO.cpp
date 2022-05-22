//
// Created by 李汇川 on 2022/5/22.
//
#include<iostream>
#include<map>
using namespace std;

// 每一个节点
struct Node {
  // 键
  int key;
  // 值
  int value;
  // 前置节点
  Node *pre;
  // 下一个节点
  Node *next;

  Node(int k, int v) : key(k), value(v), pre(NULL), next(NULL) {}

};

class FIFOCache {
 private:
  Node *head;
  // 尾节点（最近使用）
  Node *tail;
  // hashmap，存放节点
  map<int, Node *> datas;
  // 最大容量
  int capacity;
  // 当前大小
  int currentSize;
 public:
  FIFOCache() {}

  FIFOCache(int capacity) {
    // 容量
    this->capacity = capacity;
    // 当前的大小为 0
    this->currentSize = 0;
    head = new Node(-1, -1);
    tail = head;
  }

  int get(int key) {
    if (datas.count(key) == 0) {
      return -1;
    } else {
      // 获取节点
      Node *node = datas.find(key)->second;
      return node->value;
    }
  }

  void put(int key, int value) {
    // 如果已经包含
    if (datas.count(key) != 0) {
      return;
    }
    // 新建节点，拼接到链表的尾部
    Node *node = new Node(key, value);
    node->pre = tail;
    tail->next = node;
    datas.insert(pair<int, Node *>(key, node));
    tail = node;

    // 空间超出
    if (currentSize == capacity) {
      // 移除头结点
      datas.erase(datas.find(head->key));
      head = head->next;
    } else if (currentSize < capacity) {
      if (currentSize == 0) {
        head = node;
      }
      currentSize++;
    }
  }
};
int main() {
  FIFOCache cache = FIFOCache(2);
  cache.put(1, 1);
  cache.put(2, 2);
  cout << cache.get(1) << endl;
  // 删除 1，加入 3
  cache.put(3, 3);
  // 1 被删除了
  cout << cache.get(1) << endl;
  // 打印 2
  cout << cache.get(2) << endl;
  // 打印 3
  cout << cache.get(3) << endl;
  return 0;
}