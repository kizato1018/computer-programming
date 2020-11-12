#ifndef __BINTREE_H__
#define __BINTREE_H__

template <typename T>
class Node {
public:
    Node() {}
    Node(T value) : value(value) {}
    friend class bintree;
private:
    T value = 0;
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
};

template <typename T>
class bintree {
public:
    bintree(){}
    bintree(T value);
private:
    Node *root = nullptr;
};



#endif