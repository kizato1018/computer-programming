#include "bintree.h"
#include "BST.h"

#include <cstdio>
using namespace std;


template <typename T>
void BST<T>::Push(T val) {
    Node<T>* NewNode = new Node<T>(val);
    if(!this->root) {
        BinTree<T>::Push(val);
        printf("%d %d\n", this->root->val, this->size_);
    }
    Node<T>* tmp = this->root;
}