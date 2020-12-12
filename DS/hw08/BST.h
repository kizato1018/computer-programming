#ifndef __BST_H__
#define __BST_H__
#include "bintree.h"
#include <cstdio>
using namespace std;

template <typename T>
class BST : public BinTree<T> {
public:
    BST() : BinTree<T>() {}
    void Push(T val);
};

template <typename T>
void BST<T>::Push(T val) {
    Node<T>* NewNode = new Node<T>(val);
    if(!this->root) {
        BinTree<T>::Push(val);
        printf("%d %d\n", this->root->value, this->size_);
    }
    Node<T>* tmp = this->root;
}

#endif