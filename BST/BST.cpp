//
// Created by lhc456 on 2022/9/5.
//
#include<iostream>
#include <sys/time.h>                // for gettimeofday()

#include <fstream>

using namespace std;

struct BSTNode {
    int val, size;
    BSTNode *leftChild, *rightChild, *parent;
};

BSTNode *root = NULL;

int number[50001];

long getTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

BSTNode *bstInsert(BSTNode *root, int number) {
    BSTNode *current = root;
    BSTNode *previous = NULL;
    while (current) {
        current->size++;
        previous = current;
        if (current->val >= number)
            current = current->leftChild;
        else
            current = current->rightChild;
    }

    BSTNode *node = new BSTNode;
    node->val = number;
    node->leftChild = NULL;
    node->rightChild = NULL;
    node->parent = NULL;
    node->size = 1;
    if (!previous)
        return node;

    node->parent = previous;
    if (previous->val >= node->val)
        previous->leftChild = node;
    else
        previous->rightChild = node;

    return root;
}

void printBst(BSTNode *node, ofstream &fout) {
    if (node == NULL) return;
    printBst(node->leftChild, fout);
    fout << node->val << endl;
    printBst(node->rightChild, fout);
}

int findKthNumber(BSTNode *root, int K) {
    int total = 0;
    BSTNode *node = root;
    while (node) {
        int sizeLeft = 0;
        if (node->leftChild)
            sizeLeft = node->leftChild->size;
        if (total + sizeLeft + 1 == K)
            return node->val;
        else if (total + sizeLeft >= K)
            node = node->leftChild;
        else if (node->rightChild) {
            total += sizeLeft + 1;
            node = node->rightChild;
        } else return -1;
    }
    return -1;
}

BSTNode *bstFind(BSTNode *root, int number) {
    BSTNode *current = root;
    while (current) {
        if (current->val == number)
            return current;
        else if (current->val > number)
            current = current->leftChild;
        else
            current = current->rightChild;
    }
    return NULL;
}

void decreaseSize(BSTNode *node) {
    while (node) {
        node->size--;
        node = node->parent;
    }
}

BSTNode *bstDelete(BSTNode *root, BSTNode *node) {
    if (!(node->leftChild || node->rightChild)) {
        if (root == node)
            root = NULL;
        else {
            decreaseSize(node);
            if (node->parent->leftChild == node)
                node->parent->leftChild = NULL;
            else
                node->parent->rightChild = NULL;
            node->parent = NULL;
        }
    } else if (node->leftChild && !node->rightChild) {
        if (root == node) {
            root = node->leftChild;
            node->leftChild->parent = NULL;
        } else {
            decreaseSize(node);
            node->leftChild->parent = node->parent;
            if (node == node->parent->leftChild)
                node->parent->leftChild = node->leftChild;
            else
                node->parent->rightChild = node->leftChild;
        }
    } else if (node->rightChild && !node->leftChild) {
        if (root == node) {
            root = node->rightChild;
            node->rightChild->parent = NULL;
        } else {
            decreaseSize(node);
            node->rightChild->parent = node->parent;
            if (node == node->parent->leftChild)
                node->parent->leftChild = node->rightChild;
            else
                node->parent->rightChild = node->rightChild;
        }
    } else {
        BSTNode *replaceNode = node->leftChild;
        while (replaceNode->rightChild)
            replaceNode = replaceNode->rightChild;
        decreaseSize(replaceNode);
        if (replaceNode->leftChild)
            replaceNode->leftChild->parent = replaceNode->parent;
        if (replaceNode == replaceNode->parent->leftChild)
            replaceNode->parent->leftChild = replaceNode->leftChild;
        else
            replaceNode->parent->rightChild = replaceNode->leftChild;

        replaceNode->leftChild = node->leftChild;
        replaceNode->rightChild = node->rightChild;
        if (node->leftChild)
            node->leftChild->parent = replaceNode;
        node->rightChild->parent = replaceNode;
        replaceNode->parent = node->parent;
        if (node->parent)
            if (node == node->parent->leftChild)
                node->parent->leftChild = replaceNode;
            else
                node->parent->rightChild = replaceNode;
        if (root == node)
            root = replaceNode;
        replaceNode->size = 1;
        if (replaceNode->leftChild)
            replaceNode->size += replaceNode->leftChild->size;
        if (replaceNode->rightChild)
            replaceNode->size += replaceNode->rightChild->size;
    }
    delete node;
    return root;
}

int main() {
    ios::sync_with_stdio(false);

    ifstream fin("1.in");
    ofstream fout("1.out");
    cout.tie(NULL);

    int start_time = getTime();

    int n;
    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> number[i];
        root = bstInsert(root, number[i]);
    }
    fin.close();

    printBst(root, fout);

    cout << findKthNumber(root, 8) << endl;

    for (int i = n - 1; i >= 0; i--) {
        BSTNode *node = bstFind(root, number[i]);
        if (node)
            root = bstDelete(root, node);
        else
            cout << "Cannot find node with value: " << number[i] << endl;
    }

    cout << "Empty Tree? : " << (root == NULL ? "Yes" : "No") << endl;
    int end_time = getTime();
    cout << "Total time: " << (end_time - start_time + 0.0) / 1000 << "(s)" << endl;

    fout.close();
    return 0;
}