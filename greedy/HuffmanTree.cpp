//
// Created by 李汇川 on 2022/6/4.
//
#include<iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
using namespace std;

class Node {
 public:
  string chars = "";
  // 字符出现的评率
  int frequence = 0;
  // 父节点
  Node *parent;
  // 左节点
  Node *left;
  // 右节点
  Node *right;

  // 叶子节点
  bool isLeaf() {
    return chars.size() == 1;
  }

  // 根节点
  bool isRoot() {
    return parent == NULL;
  }

  // 是否是左节点
  bool isLeftChild() {
    return parent != NULL && this == parent->left;
  }
};

// 树
class Tree {
  // 根节点
 public:
  Node *root;

  Node *getRoot() {
    return root;
  }

  void setRoot(Node *root) {
    this->root = root;
  }
};
struct cmp {
  bool operator()(Node *a, Node *b) {
    if (b->frequence < a->frequence) {
      return true;
    } else if (b->frequence == a->frequence) {
      return b->chars.size() > a->chars.size();
    }
    return false;
  }
};

class HuffmanTree {
 public:
  HuffmanTree() {

  }

  string encode(
      string str,
      map<char, int> &frequenceMap
  ) {
    if (str.compare("") == 0) {
      return "";
    }
    // 叶子节点
    vector<Node *> leafs;
    // 建树
    buildTree(frequenceMap, leafs);
    // 编码之后的信息，每个字符对应二进制
    map<char, string> binaryMap = buildBinaryInfo(leafs);

    // 拼接起来
    string buffer;
    for (char c: str) {
      buffer.append(binaryMap.find(c)->second);
    }

    return buffer;
  }
  string decodeStr(string binary, map<char, int> &frequenceMap);

  // 统计字符出现的次数/频率
  map<char, int> getFrequency(string chars) {
    map<char, int> maps;
    for (char c: chars) {
      // 已经出现过
      if (maps.count(c) != 0) {
        // 频次加一
        map<char, int>::iterator iter;
        iter = maps.find(c);
        int value = iter->second;
        maps.erase(iter);
        maps.insert(pair<char, int>(c, value + 1));
      } else {
        // 首次出现，频次为 1
        maps.insert(pair<char, int>(c, 1));
      }
    }
    return maps;
  }

  // 打印
  void printFrequency(map<char, int> &frequencyMap) {
    std::map<char, int>::iterator it;
    for (it = frequencyMap.begin(); it != frequencyMap.end(); ++it) {
      cout << it->first << " : " << it->second << endl;
    }
  }

 private:
// 按照出现频率建树
  Tree *buildTree(map<char, int> &frequencyMap, vector<Node *> &leafs) {
    // 转字符数组
    std::map<char, int>::iterator it;
    vector<char> keys;
    for (it = frequencyMap.begin(); it != frequencyMap.end(); ++it) {
      keys.push_back(it->first);
    }

    // 初始化节点加到优先队列，频率高的在前面
    priority_queue<Node *, vector<Node *>, cmp> queue;
    for (char c: keys) {
      Node *node = new Node();
      // 字符
      node->chars = c;
      // 出现频率
      node->frequence = frequencyMap.find(c)->second;
      // 添加到队列
      queue.push(node);
      // 添加到叶子节点
      leafs.push_back(node);
    }
    while (queue.size() > 1) {
      // 弹出两个最低频的接点
      Node *node1 = queue.top();
      queue.pop();
      Node *node2 = queue.top();
      queue.pop();

      // 合成新的节点
      Node *parent = new Node();
      // 字符串合并
      parent->chars = node1->chars + node2->chars;
      // 频率合并
      parent->frequence = node1->frequence + node2->frequence;

      parent->left = node1;
      parent->right = node2;

      node1->parent = parent;
      node2->parent = parent;

      queue.push(parent);
    }

    Tree *tree = new Tree();
    // 最后一个是根节点
    tree->root = queue.top();
    queue.pop();
    return tree;
  };
  // 对每个字符进行编码，也就是按照二进制来匹配
  map<char, string> buildBinaryInfo(vector<Node *> &leafs) {
    map<char, string> binaryMap;
    for (Node *node: leafs) {
      // 获取节点的第一个字符（其实叶子节点只有一个字符）
      char c = node->chars[0];
      string binary = "";
      // 暂存当前节点
      Node *tempNode = node;
      // 从叶子节点，开始往上，到根节点
      do {
        // 如果是左节点，则是 0
        if (tempNode->isLeftChild()) {
          binary = "0" + binary;
        } else {
          // 右节点，是 1
          binary = "1" + binary;
        }
        // 到上一层
        tempNode = tempNode->parent;
        // 直到没有父节点
      } while (tempNode->parent != NULL);
      // 存储起来
      binaryMap.insert(pair<char, string>(c, binary));
    }

    return binaryMap;
  }
};

int main() {
  string str = "Hello";
  cout << "原字符串：" << str << endl;
  // 出现频率统计
  HuffmanTree *huffman_tree = new HuffmanTree();
  map<char, int> frequenceMap = huffman_tree->getFrequency(str);
  huffman_tree->printFrequency(frequenceMap);
  // 编码二进制字符串
  string binary = huffman_tree->encode(str, frequenceMap);
  // 解码
  string decode = huffman_tree->decodeStr(binary, frequenceMap);
  cout << "编码后二进制：" << binary << endl;
  cout << "解压字符串：" << decode << endl;
  cout <<
       "长度变化：" << str.length() * 8 << " ===> " << binary.length()
       << endl;
  return 0;
}