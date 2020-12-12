#ifndef __BINTREE_H__
#define __BINTREE_H__

template <typename T>
struct Node{
public:
    Node() {}
    Node(T val) : value(val) {}
    bool isFull() { return left != nullptr & right != nullptr; }
    bool operator < (const Node a) const {return value < a.value;}
    bool operator > (const Node a) const {return a < *this;}
    bool operator <= (const Node a) const {return !(*this > a);}
    bool operator >= (const Node a) const {return !(*this < a);}
    T value;
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
};

template <typename T>
class BinTree{
public:
    BinTree() {}
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
    void Delete(Node<T>* node);
    bool isEmpty() {return size_ == 0;}
    int Size() {return size_;}

private:
    Node<T>** Prefix_(Node<T>** arr, Node<T>* cur) const;
    Node<T>** Infix_(Node<T>** arr, Node<T>* cur) const;
    Node<T>** Postfix_(Node<T>** arr, Node<T>* cur) const;
    Node<T>** Resize();

protected:
    Node <T>* root = nullptr;
    Node <T>* LeftMost = nullptr;
    Node <T>* Last = nullptr;
    int size_ = 0;
};


template <typename T>
Node<T>** BinTree<T>::Prefix_(Node<T>** arr, Node<T>* cur) const {
    if(!cur) return arr;
    *arr = cur;
    ++arr;
    arr = Prefix_(arr, cur->left);
    arr = Prefix_(arr, cur->right);
    return arr;
}
template <typename T>
Node<T>** BinTree<T>::Infix_(Node<T>** arr, Node<T>* cur) const {
    if(!cur) return arr;
    arr = Prefix_(arr, cur->left);
    *arr = cur;
    ++arr;
    arr = Prefix_(arr, cur->right);
    return arr;
}
template <typename T>
Node<T>** BinTree<T>::Postfix_(Node<T>** arr, Node<T>* cur) const {
    if(!cur) return arr;
    arr = Prefix_(arr, cur->left);
    arr = Prefix_(arr, cur->right);
    *arr = cur;
    ++arr;
    return arr;
}
template <typename T>
Node<T>** BinTree<T>::Prefix() const {
    Node<T>** arr = new Node<T>*[size_];
    Prefix_(arr, root);
    return arr;
}
template <typename T>
Node<T>** BinTree<T>::Infix() const {
    Node<T>** arr = new Node<T>*[size_];
    Infix_(arr, root);
    return arr;
}
template <typename T>
Node<T>** BinTree<T>::Postfix() const {
    Node<T>** arr = new Node<T>*[size_];
    Postfix_(arr, root);
    return arr;
}
template <typename T>
Node<T>** BinTree<T>::BFS() const {
    Node<T>** arr = new Node<T>*[size_];
    arr[0] = root;
    for(int i = 1, j = 0; i < size_; ++i, ++j) {
        arr[i] = arr[j]->left;
        arr[++i] = arr[j]->right;
    }
    return arr;
}
template <typename T>
Node<T>* BinTree<T>::operator[] (int index) const {
    if(index < 0 || index >= size_) return nullptr;
    Node<T>* cur = root;
    while(cur != nullptr && index > 0) {
        cur = (index % 2) ? cur->left : cur->right;
        index >>= 1;
    }
    return cur;
}

template <typename T>
Node<T>* BinTree<T>::Find(T val) const {
    Node<T>** arr = new Node<T>*[size_]{nullptr};
    Node<T>* tmp = nullptr;
    arr[0] = root;
    if(arr[0]->value == val) {
        tmp = arr[0];
        delete arr;
        return tmp;
    }
    for(int i = 1, j = 0; i < size_; ++i, ++j) {
        arr[i] = arr[j]->left;
        if(arr[i]->value == val) {
            tmp = arr[i];
            break;
        }
        arr[++i] = arr[j]->right;
        if(arr[i]->value == val) {
            tmp = arr[i];
            break;
        }
    }
    delete arr;
    return tmp;
}

// template <typename T>
// void BinTree<T>::InsertLeft(Node<T>* left, T val) {
//     Node<T>* tmp = new Node<T>(val);
//     tmp->left = left;
//     left->parent = tmp;
//     if(left == root) 
//         root = tmp;
//     ++size_;
// }
// template <typename T>
// void BinTree<T>::InsertRight(Node<T>* right, T val) {
//     Node<T>* tmp = new Node<T>(val);
//     tmp->right = right;
//     right->parent = tmp;
//     ++size_;
// }
// template <typename T>
// void BinTree<T>::PushLeftMost(T val) {
//     Node<T>* tmp = new Node<T>(val);
//     tmp->parent = LeftMost;
//     LeftMost->left = tmp;
//     LeftMost = tmp;
//     ++size_;
    
// }

template <typename T>
void BinTree<T>::Push(T val) {
    Node<T>* tmp = new Node<T>(val);
    Node<T>* parent = root;
    if(isEmpty()) {
        root = tmp;
        LeftMost = tmp;
        Last = tmp;
        ++size_;
        return;
    }
    else if(size_ > 3) {
        parent = (*this)[(size_-2)/2];
    }
    tmp->parent = parent;
    if(!parent->left) {
        parent->left = tmp;
        if(parent == LeftMost)
            LeftMost = tmp;
    }
    else 
        parent->right = tmp;
    Last = tmp;
    ++size_;
}


#endif