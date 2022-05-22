//
// Created by 李汇川 on 2022/5/22.
//
#include<iostream>
#include<map>
#include<set>
using namespace std;

// 每一个节点
struct Node {
  // 使用次数，最后使用时间戳
  long usedCount = 0;
  long lastUsedTime = 0;
  // 键
  int key;
  // 值
  int value;

  Node(long usedCount, long lastUsedTime, int key, int value) {
    this->usedCount = usedCount;
    this->lastUsedTime = lastUsedTime;
    this->key = key;
    this->value = value;
  }

};
struct comp {
  bool operator()(const Node *node1, const Node *node2) const {
    if (node1->key == node2->key)
      return false;
    else {
      if (node1->usedCount != node2->usedCount) {
        return node1->usedCount < node2->usedCount;      //降序
      } else {
        return node1->lastUsedTime > node2->lastUsedTime;
      }
    }
  }
};
class LFUCache {
 private:
  // 容量
  int capacity;
  // 时间戳
  int timeStamp = 0;
  // 键值对
  map<int, Node *> map;
  // 按照频次排序的节点
  set<Node *, comp> frequencyNodes;
 public:
  LFUCache() {}

  LFUCache(int capacity) {
    // 容量
    this->capacity = capacity;
  }

  int get(int key) {
    // 如果不包含，直接返回
    if (map.count(key) == 0) {
      return -1;
    }
    // 获取值
    Node *node = map.find(key)->second;
    // 删掉旧的值
    frequencyNodes.erase(node);
    // 更新使用次数
    node->usedCount = node->usedCount + 1;
    // 更新最后一次使用的时间
    node->lastUsedTime = ++timeStamp;
    // 重新添加
    frequencyNodes.insert(node);
    // 更新节点的值
    map.insert(pair<int, Node *>(key, node));
    return node->value;
  }

  void put(int key, int value) {
    // 容量是不是等于 0
    if (capacity == 0) {
      return;
    }
    // 之前不包含该 key
    if (map.count(key) == 0) {
      // 容量超出
      if (map.size() == capacity) {
        // 移除第一个值（使用频率最低）
        set<Node *>::iterator it = frequencyNodes.begin();
        map.erase(map.find((*it)->key));
        // 移除第一个
        frequencyNodes.erase(frequencyNodes.begin());
      }
      // 创建新节点
      Node *node = new Node(1, ++timeStamp, key, value);
      // 添加
      map.insert(pair<int, Node *>(key, node));
      frequencyNodes.insert(node);
    } else {
      Node *node = map.find(key)->second;
      // 移除掉，为了更新频率
      frequencyNodes.erase(node);
      // 更新使用次数
      node->usedCount = node->usedCount + 1;
      node->lastUsedTime = ++timeStamp;
      node->value = value;
      frequencyNodes.insert(node);
      // 添加
      map.insert(pair<int, Node *>(key, node));
    }
  }
};
int main() {
  LFUCache cache = LFUCache(2);
  cache.put(1, 1);
  cache.put(2, 2);
  // 2 的使用频率增加
  cout << cache.get(2) << endl;
  // 移除 1
  cache.put(3, 3);
  // 1 已经被移除
  cout << cache.get(1) << endl;
  // 2 还在
  cout << cache.get(2) << endl;
  // 增加 3 的频次
  cout << cache.get(3) << endl;
  cout << cache.get(3) << endl;
  cout << cache.get(3) << endl;
  // 移除 2 ，新增 4
  cache.put(4, 4);

  cout << cache.get(3) << endl;
  return 0;
}