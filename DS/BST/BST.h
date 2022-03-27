//
// Created by 李汇川 on 2022/3/27.
//

#ifndef PLAY_WITH_ALGO_DS_BST_BST_H_
#define PLAY_WITH_ALGO_DS_BST_BST_H_
#include <stack>
#include <iostream>
#include <queue>

template<typename T>
class Node {
 public:
  T e;
  Node<T> *left, *right;

  Node(T e) {
    this->e = e;
    left = nullptr;
    right = nullptr;
  }
};

template<typename T>
class BST {
 public:
  BST() {
    root = nullptr;
    size = 0;
  }

  int getSize() {
    return size;
  }

  bool isEmpty() {
    return size == 0;
  }

  void add(T e) {
    if (root == nullptr) {
      root = new Node<T>(e);
      size++;
    } else {
      add(root, e);
    }
  }

  void add(Node<T> *node, T e) {
    if (node->e == e) {
      return;
    } else if (node->e > e && node->left == nullptr) {
      node->left = new Node<T>(e);
      size++;
      return;
    } else if (node->e < e && node->right == nullptr) {
      node->right = new Node<T>(e);
      size++;
      return;
    }

    if (node->e > e) {
      add(node->left, e);
    } else {
      add(node->right, e);
    }
  }

  bool contains(T e) {
    return contains(root, e);
  }

  void preOrder() {
    preOrder(root);
  }

  void inOrder() {
    inOrder(root);
    std::cout << std::endl;
  }

  void postOrder() {
    postOrder(root);
    std::cout << std::endl;
  }
  void generateBSTString(Node<T> *node, int depth) {
    if (node == nullptr) {
      generateDepthString(depth);
      std::cout << "NULL" << std::endl;
      return;
    }
    generateDepthString(depth);
    std::cout << node->e << std::endl;
    generateBSTString(node->left, depth + 1);
    generateBSTString(node->right, depth + 1);
  }

  void print() {
    generateBSTString(root, 0);
  }

  void preOrderNR() {
    std::stack<Node<T> *> stack;
    stack.push(root);
    while (!stack.empty()) {
      Node<T> *cur = stack.top();
      std::cout << cur->e << " ";
      stack.pop();
      if (cur->right != nullptr) {
        stack.push(cur->right);
      }
      if (cur->left != nullptr) {
        stack.push(cur->left);
      }
    }
    std::cout << std::endl;
  }

  void inOrderNR() {
    std::stack<Node<T> *> stack;
    Node<T> *cur = root;
    while (cur != nullptr || !stack.empty()) {
      while (cur != nullptr) {
        stack.push(cur);
        cur = cur->left;
      }
      if (!stack.empty()) {
        cur = stack.top();
        std::cout << cur->e << " ";
        stack.pop();
        cur = cur->right;
      }
    }
    std::cout << std::endl;
  }

  void postOrderNR() {
    std::stack<Node<T> *> stack;
    Node<T> *cur = root;
    Node<T> *temp;
    while (cur != nullptr || !stack.empty()) {
      while (cur != nullptr) {
        stack.push(cur);
        cur = cur->left;
      }
      if (!stack.empty()) {
        cur = stack.top();
        if (cur->right == temp || cur->right == nullptr) {
          std::cout << cur->e << " ";
          stack.pop();
          temp = cur;
          cur = nullptr;
        } else {
          cur = cur->right;
        }

      }
    }
    std::cout << std::endl;
  }
  void levelOrder() {
    std::queue<Node<T> *> *q = new std::queue<Node<T> *>();
    q->push(root);
    while (!q->empty()) {
      Node<T> *node = q->front();
      q->pop();
      std::cout << node->e << " ";
      if (node->left != nullptr) {
        q->push(node->left);
      }
      if (node->right != nullptr) {
        q->push(node->right);
      }
    }
    std::cout << std::endl;
  }

  T minimun() {
    assert(size > 0);
    return min(root)->e;
  }

  T maximun() {
    assert(size > 0);
    return max(root)->e;
  }

  T removeMin() {
    T ret = minimun();
    root = removeMin(root);
    return ret;
  }

  T removeMax() {
    T ret = maximun();
    root = removeMax(root);
    return ret;
  }

  void remove(T e) {
    root = remove(root, e);
  }

 private:
  Node<T> *root;
  int size;
  bool contains(Node<T> *node, T e) {
    if (node == nullptr) {
      return false;
    }

    if (node->e == e) {
      return true;
    } else if (node->e > e) {
      return contains(node->left, e);
    } else {
      return contains(node->right, e);
    }
  }

  void preOrder(Node<T> *node) {
    if (node == nullptr) {
      return;
    }
    std::cout << node->e << std::endl;
    preOrder(node->left);
    preOrder(node->right);
  }

  void generateDepthString(int depth) {
    for (int i = 0; i < depth; ++i) {
      std::cout << "--";
    }
  }

  void inOrder(Node<T> *node) {
    if (node == nullptr) {
      return;
    }
    inOrder(node->left);
    std::cout << node->e << " ";
    inOrder(node->right);
  }

  void postOrder(Node<T> *node) {
    if (node == nullptr) {
      return;
    }
    postOrder(node->left);
    postOrder(node->right);
    std::cout << node->e << " ";
  }

  Node<T> *min(Node<T> *node) {
    if (node->left == nullptr)
      return node;
    return min(node->left);
  }

  Node<T> *max(Node<T> *node) {
    if (node->right == nullptr)
      return node;
    return max(node->right);
  }
  Node<T> *removeMin(Node<T> *node) {
    if (node->left == nullptr) {
      Node<T> *rightNode = node->right;
      delete node;
      size--;
      return rightNode;
    }
    node->left = removeMin(node->left);
    return node;
  }
  Node<T> *removeMax(Node<T> *node) {
    if (node->right == nullptr) {
      Node<T> *leftNode = node->left;
      delete node;
      size--;
      return leftNode;
    }
    node->right = removeMax(node->right);
    return node;
  }

  Node<T> *remove(Node<T> *node, T e) {
    if (node == nullptr) {
      return nullptr;
    }
    if (e < node->e) {
      node->left = remove(node->left, e);
      return node;
    } else if (e > node->e) {
      node->right = remove(node->right, e);
      return node;
    } else {
      if (node->left == nullptr) {
        Node<T> *rightNode = node->right;
        delete node;
        size--;
        return rightNode;
      }

      if (node->right == nullptr) {
        Node<T> *leftNode = node->left;
        delete node;
        size--;
        return leftNode;
      }

      Node<T> *successor = new Node<T>(min(node->right)->e);
      size++;

      successor->right = removeMin(node->right);
      successor->left = node->left;
      node->left = node->right = nullptr;
      delete node;
      size--;

      return successor;
    }
  }

};

#endif //PLAY_WITH_ALGO_DS_BST_BST_H_
