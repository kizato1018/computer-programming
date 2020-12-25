#ifndef __BST_H__
#define __BST_H__
#include "bintree.h"
#include <iostream>
using namespace std;

template <typename T>
class BST : public BinTree<T> {
public:
    BST() : BinTree<T>() {}
    void Show() const;
    void Show(Node<T>**) const;
    BST<T> Push(T val);
    Node<T>* Find(T val);
    Node<T>* Successor(Node<T>* cur);
    bool Delete(T val);
    bool Delete(Node<T>*);
};

template <typename T>
void BST<T>::Show() const {
    Node<T>** arr = BinTree<T>::BFS();
    for(int i = 0; i < this->Size(); ++i) {
        if(!arr[i]->left_thread)
            cout << arr[i]->value << " -> " << arr[i]->left->value << " L" << endl;
        if(!arr[i]->right_thread)
            cout << arr[i]->value << " -> " << arr[i]->right->value << " R" << endl;
    }
    cout << endl;
}


template <typename T>
void BST<T>::Show(Node<T>** arr) const {
    for(int i = 0; i < this->Size() && arr[i]; ++i) {
        cout << arr[i]->value << endl;
    }
}

template <typename T>
BST<T> BST<T>::Push(T val) {
    if(this->isEmpty()) {
        BinTree<T>::Push(val);
        return *this;
    }
    Node<T>* NewNode = new Node<T>(val);
    Node<T>* parent = this->root->left;
    Node<T>* lthread = this->root;
    Node<T>* rthread = this->root;
    while(1) {
        if(val < parent->value) {
            rthread = parent;
            if(parent->left_thread) {
                NewNode->left = lthread;
                NewNode->right = rthread;
                parent->left = NewNode;
                parent->left_thread = false;
                if(parent == this->left_most)
                    this->left_most = NewNode;
                // cout << parent->value << "->" << val << " L" << endl;
                // printf("%d->%d L\n", parent->value, val);
                break;
            }
            parent = parent->left;
        }
        else {
            lthread = parent;
            if(parent->right_thread) {
                NewNode->left = lthread;
                NewNode->right = rthread;
                parent->right = NewNode;
                parent->right_thread = false;
                // cout << parent->value << "->" << val << " R" << endl;
                // printf("%d->%d R\n", parent->value, val);
                break;
            }
            parent = parent->right;
        }
    }
    NewNode->parent = parent;
    this->last = NewNode;
    ++this->size_;
    return *this;
}

template <typename T>
Node<T>* BST<T>::Find(T val) {
    if(this->isEmpty()) return nullptr;
    Node<T>* cur = this->root->left;
    while(1) {
        if(val < cur->value) {
            if(cur->left_thread) break;
            cur = cur->left;
        }
        else if(cur->value < val) {
            if(cur->right_thread) break;
            cur = cur->right;
        }
        else break;
    }
    if(cur->value != val) return nullptr;
    return cur;
}

template <typename T>
Node<T>* BST<T>::Successor(Node<T>* cur) {
    if(!cur) return nullptr;
    if(!cur->right_thread) {
        cur = cur->right;
        while(!cur->left_thread) cur = cur->left;
        return cur;
    }
    Node<T>* par = cur->parent;
    while(par != this->root && par->right == cur) {
        cur = par;
        par = cur->parent;
    }
    if(par == this->root) return nullptr;
    return par;
}

template <typename T>
bool BST<T>::Delete(Node<T>* cur) {
    if(!cur) return false;
    if(cur->Childcnt() == 0) {
        if(cur->parent->left == cur) cur->parent->left = nullptr;
        else cur->parent->right = nullptr;
        if(cur == this->left_most) this->left_most = cur->parent;
        if(cur == this->last) this->last = nullptr;
        if(cur == this->root) this->root = nullptr;
        --this->size_;
        delete cur;
    }
    else if(cur->Childcnt() == 1) {
        if(cur->left) {
            if(cur == this->root) {
                this->root = cur->left;
                cur->parent = nullptr;
            }
            else if(cur->parent->left == cur) {
                cur->parent->left = cur->left;
                cur->left->parent = cur->parent;
            }
            else {
                cur->parent->right = cur->left;
                cur->left->parent = cur->parent;
            }
        }
        else {
            if(cur == this->root) {
                this->root = cur->right;
                cur->parent = nullptr;
            }
            else if(cur->parent->left == cur) {
                cur->parent->left = cur->right;
                cur->right->parent = cur->parent;
                this->left_most = cur->right;
                while(this->left_most->left) this->left_most = this->left_most->left;
            }
            else {
                cur->parent->right = cur->right;
                cur->right->parent = cur->parent;
            }
        }
        if(cur == this->last) this->last = nullptr;
        --this->size_;
        delete cur;
    }
    else if(cur->Childcnt() == 2) {
        Node<T>* local_max = cur->left;
        while(local_max->right) local_max = local_max->right;
        if(local_max->parent != cur) {
            local_max->parent->right = local_max->left;
            local_max->left->parent = local_max->parent;
        }
        if(cur->parent->left == cur) 
            cur->parent->left = local_max;
        else 
            cur->parent->right = local_max;
        local_max->parent = cur->parent;
        local_max->left = (cur->left != local_max) ? cur->left : nullptr;
        local_max->right = cur->right;
        if(cur == this->root) {
            this->root = local_max;
            local_max->parent = nullptr;
        }
        if(cur == this->last) this->last = nullptr;
        --this->size_;
        delete cur;
    }
    else {
        printf("Error...\n");
        return false;
    }
    return true;
}

template <typename T>
bool BST<T>::Delete(T val) {
    Node<T>* cur = this->Find(val);
    return this->Delete(cur);
}


#endif