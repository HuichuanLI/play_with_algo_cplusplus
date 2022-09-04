//
// Created by lhc456 on 2022/9/5.
//
#include <iostream>

using namespace std;

struct BSTNode {
    int val, size;
    BSTNode *leftchid, *rightchild, *parent;
};

int number[50001];

BSTNode *bstInsert(BSTNode *root, int number) {
    BSTNode *current = root;
    BSTNode *previous = NULL;
    while (current) {
        current->size++;
        previous = current;
        if (current->val >= number) {
            current = current->leftchid;
        } else {
            current = current->rightchild;
        }
    }


    BSTNode *node = new BSTNode;
    node->val = number;
    node->leftchid = NULL;
    node->rightchild = NULL;
    node->parent = NULL;
    node->size += 1;
    if (!previous)
        return node;
    node->parent = previous;
    if (previous->val >= node->val) {
        previous->leftchid = node;
    } else {
        previous->rightchild = node;
    }
    return root;
}

int findKthNumber(BSTNode *root, int K) {
    int total = 0;
    BSTNode *node = root;
    while (node) {
        int sizeLeft = 0;
        if (node->leftchid)
            sizeLeft = node->leftchid->size;
        if (total + sizeLeft + 1 == K) {
            return node->val;
        } else if (total + sizeLeft >= K) {
            node = node->leftchid;
        } else if (node->rightchild) {
            total += sizeLeft + 1;
            node = node->rightchild;
        } else {
            return -1;
        }
    }
    return -1;
}
