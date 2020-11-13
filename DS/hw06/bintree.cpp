#include "bintree.h"
#include <iostream>

using namespace std;

bool Node::operator<(const Node a) {
    return (value == '+' || value == '-') && (a.value == '*' || a.value == '/');
}
bool Node::operator>=(const Node a) {
    return !(*this < a);
}

expretree& expretree::push(int v) {
    Node *newNode;
    newNode = new Node(v, Operand, level);
    if(root == nullptr) {
        // cout << "operand push 1" << endl;
        root = newNode;
    }
    else {
        // cout << (char)prev->value << "  operand push 2" << endl;
        prev->right = newNode;
        newNode->parent = prev;
    }
    prev = newNode;
    return *this;
}
expretree& expretree::push(char v) {
    Node *newNode, *lc = prev;
    newNode = new Node(v, Operator, level);

    if(lc->parent != nullptr)
        lc = lc->parent;
    while(lc->parent != nullptr && (newNode->level < lc->level || (lc->isFull() && *lc >= *newNode && lc->level >= lc->parent->level))) lc = lc->parent;
    if(lc->tag == Operand || (lc->level == newNode->level && *lc >= *newNode)) {
        // cout << "operator push 1" << endl;
        lc->parent = newNode;
        newNode->left = lc;
        if(lc == root) 
            root = newNode;
    }
    else {
        // cout << "operator push 2" << endl;
        newNode->left = lc->right;
        newNode->left->parent = newNode;
        lc->right = newNode;
        newNode->parent = lc;
    }
    prev = newNode;
    return *this;
}

void expretree::postfix(Node* tmp) {
    if(tmp->left != nullptr) postfix(tmp->left);
    if(tmp->right != nullptr) postfix(tmp->right);
    switch(tmp->tag) {
        case Operand:
            cout << (int)tmp->value << " ";
            break;
        case Operator:
            cout << (char)tmp->value << " ";
            break;
        default:
            cout << "error" << endl;
            break;
    }
    
}