//
// Created by 李汇川 on 2022/5/22.
//
#include<iostream>
#include<map>
#include<set>
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

  Node(Node *pre, Node *next, int key, int value) {
    this->pre = pre;
    this->value = value;
    this->key = key;
    this->next = next;
  }

};

class LRUCache {
 private:
  // 头结点（最远使用）
  Node *head;
  // 尾节点（最近使用）
  Node *tail;
  // hashmap，存放节点
  map<int, Node *> datas;
  // 最大容量
  int capacity = 0;
  // 当前大小
  int currentSize = 0;
 public:
  LRUCache() {}

  LRUCache(int capacity) {
    // 容量
    this->capacity = capacity;
    // 当前的大小为 0
    this->currentSize = 0;
    // 头节点初始化
    head = new Node(NULL, NULL, -1, -1);
    tail = head;
  }

  int get(int key) {
    if (datas.count(key) == 0) {
      return -1;
    }
    // 获取节点
    Node *node = datas.find(key)->second;
    if (node->key == tail->key) {
      return tail->value;
    }

    // 后一个节点
    Node *nextNode = node->next;
    // 前面一个节点
    Node *prevNode = node->pre;
    // 如果是第一个节点
    if (node->key == head->key) {
      nextNode->pre = NULL;
      head = nextNode;
    } else {
      // 从链表移除
      prevNode->next = nextNode;
      nextNode->pre = prevNode;
    }

    // 拼接到链表的尾部
    node->pre = tail;
    tail->next = node;
    tail = node;
    tail->next = NULL;
    return node->value;
  }

  void put(int key, int value) {
    // 如果已经包含
    if (datas.count(key) != 0) {
      return;
    }
    // 新建节点，拼接到链表的尾部
    Node *node = new Node(tail, NULL, key, value);
    tail->next = node;
    datas.insert(pair<int, Node *>(key, node));
    tail = node;

    // 空间超出
    if (currentSize == capacity) {
      datas.erase(datas.find(head->key));
      head = head->next;
      head->pre = NULL;
    } else if (currentSize < capacity) {
      if (currentSize == 0) {
        head = node;
      }
      currentSize++;
    }
  }
};
int main() {
  LRUCache cache = LRUCache(2);
  cache.put(1, 1);
  cache.put(2, 2);
  cout << cache.get(1) << endl; // 返回 1
  cache.put(3, 3); // 该操作会使得 key 2 作废
  cout << cache.get(2) << endl; // 返回 -1 (未找到)
  cache.put(4, 4); // 该操作会使得 key 1 作废
  cout << cache.get(1) << endl; // 返回 -1 (未找到)
  cout << cache.get(3) << endl; // 返回 -1 (未找到)
  cout << cache.get(4) << endl; // 返回  4
  return 0;
}