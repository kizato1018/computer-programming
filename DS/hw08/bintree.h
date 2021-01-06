#ifndef __BINTREE_H__
#define __BINTREE_H__

#include <cstdio>

template <typename T>
struct Node{
    Node() {}
    Node(T val) : value(val) {}
    bool isLeaf() { return left_thread & right_thread; }
    bool operator < (const Node a) const {return value < a.value;}
    bool operator > (const Node a) const {return a < *this;}
    bool operator <= (const Node a) const {return !(*this > a);}
    bool operator >= (const Node a) const {return !(*this < a);}
    int Childcnt() const {return (!left_thread) + (!right_thread);}
    T value;
    Node *parent = this;
    Node *left = this;
    Node *right = this;
    bool left_thread = true;
    bool right_thread = true;
};

template <typename T>
class BinTree{
public:
    BinTree() {root->left_thread = false; root->right_thread = false;}
    Node<T>** Prefix() const;
    Node<T>** Infix() const;
    Node<T>** Postfix() const;
    Node<T>** BFS() const;
    Node<T>* operator [] (int index) const;
    Node<T>* Find(T val) const; 
    // void InsertLeft(Node<T>* left, T val);
    // void InsertRight(Node<T>* right, T val);
    // void PushLeftMost(T val);
    void Push(T val);
    // void Delete(Node<T>* node);
    bool isEmpty() const {return size_ == 0;}
    int Size() const {return size_;}

private:
    Node<T>** Prefix_(Node<T>** arr, Node<T>* cur) const;
    Node<T>** Infix_(Node<T>** arr, Node<T>* cur) const;
    Node<T>** Postfix_(Node<T>** arr, Node<T>* cur) const;
    Node<T>** Resize();

protected:
    Node <T>* root = new Node<T>();
    Node <T>* left_most = nullptr;
    Node <T>* last = nullptr;
    int size_ = 0;
};


template <typename T>
Node<T>** BinTree<T>::Prefix_(Node<T>** arr, Node<T>* cur) const {
    if(cur->isLeaf()) {
        *arr = cur;
        ++arr;
        return arr;
    }
    *arr = cur;
    ++arr;
    if(!cur->left_thread)
        arr = Prefix_(arr, cur->left);
    if(!cur->right_thread)
        arr = Prefix_(arr, cur->right);
    return arr;
}
template <typename T>
Node<T>** BinTree<T>::Infix_(Node<T>** arr, Node<T>* cur) const {
    if(cur->isLeaf()) {
        *arr = cur;
        ++arr;
        return arr;
    }
    if(!cur->left_thread)
        arr = Infix_(arr, cur->left);
    *arr = cur;
    ++arr;
    if(!cur->right_thread)
        arr = Infix_(arr, cur->right);
    return arr;
}
template <typename T>
Node<T>** BinTree<T>::Postfix_(Node<T>** arr, Node<T>* cur) const {
    if(cur->isLeaf()) {
        *arr = cur;
        ++arr;
        return arr;
    }
    if(!cur->left_thread)
        arr = Postfix_(arr, cur->left);
    if(!cur->right_thread)
        arr = Postfix_(arr, cur->right);
    *arr = cur;
    ++arr;
    return arr;
}
template <typename T>
Node<T>** BinTree<T>::Prefix() const {
    if(root->left == root) return nullptr;
    Node<T>** arr = new Node<T>*[size_];
    Prefix_(arr, root->left);
    return arr;
}
template <typename T>
Node<T>** BinTree<T>::Infix() const {
    if(root->left == root) return nullptr;
    Node<T>** arr = new Node<T>*[size_];
    Infix_(arr, root->left);
    return arr;
}
template <typename T>
Node<T>** BinTree<T>::Postfix() const {
    if(root->left == root) return nullptr;
    Node<T>** arr = new Node<T>*[size_];
    Postfix_(arr, root->left);
    return arr;
}
template <typename T>
Node<T>** BinTree<T>::BFS() const {
    if(root->left == root) return nullptr;
    Node<T>** arr = new Node<T>*[size_];
    arr[0] = root->left;
    for(int i = 0, j = 0; j < size_; ++j) {
        if(!arr[j]->left_thread)
            arr[++i] = arr[j]->left;
        if(!arr[j]->right_thread)
            arr[++i] = arr[j]->right;
    }
    return arr;
}
template <typename T>
Node<T>* BinTree<T>::operator[] (int index) const {
    if(index < 0 || index >= size_) return nullptr;
    return BFS()[index];
}

template <typename T>
Node<T>* BinTree<T>::Find(T val) const {
    Node<T>** arr = BFS();
    for(int i = 0; i < size_; ++i) {
        if(val == arr[i].value)
            return arr[i];
    }
    return nullptr;
}


// template <typename T>
// void BinTree<T>::InsertLeft(Node<T>* left, T val) {
//     Node<T>* NewNode = new Node<T>(val);
//     NewNode->left = left;
//     left->parent = NewNode;
//     if(left == root) 
//         root = NewNode;
//     ++size_;
// }
// template <typename T>
// void BinTree<T>::InsertRight(Node<T>* right, T val) {
//     Node<T>* NewNode = new Node<T>(val);
//     NewNode->right = right;
//     right->parent = NewNode;
//     ++size_;
// }
// template <typename T>
// void BinTree<T>::Pushleft_most(T val) {
//     Node<T>* NewNode = new Node<T>(val);
//     NewNode->parent = left_most;
//     left_most->left = NewNode;
//     left_most = NewNode;
//     ++size_;
    
// }

template <typename T>
void BinTree<T>::Push(T val) {
    Node<T>* NewNode = new Node<T>(val);
    Node<T>* parent = root->left;
    Node<T>* lthread = root;
    Node<T>* rthread = root;
    if(isEmpty()) {
        root->left = NewNode;
        NewNode->left = lthread;
        NewNode->right = rthread;
        NewNode->parent = root;
        left_most = NewNode;
        last = NewNode;
        ++size_;
        return;
    }
    else {
        parent = (*this)[(size_-1)/2];
        int i = size_;
        while(i % 2 == 0) i /= 2;
        if(i == 1) lthread = root;
        else lthread = (*this)[i/2];
        while(i % 2 == 1) i /= 2;
        if(i == 0) rthread = root;
        else rthread = (*this)[i/2];
        // printf("%d P\n", parent->value);
    }
    NewNode->parent = parent;
    if(parent->left_thread) {
        NewNode->left = lthread;
        NewNode->right = rthread;
        parent->left = NewNode;
        parent->left_thread = false;
        if(parent == left_most)
            left_most = NewNode;
        printf("%d->%d L\n", parent->value, val);
    }
    else {
        NewNode->left = lthread;
        NewNode->right = rthread;
        parent->right = NewNode;
        parent->right_thread = false;
        printf("%d->%d R\n", parent->value, val);
    }
    last = NewNode;
    ++size_;
}


#endif