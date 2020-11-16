#include "bintree.h"
#include <iostream>
#include <stack>
#include <cstdlib>

using namespace std;

double cal(double l, double r, char opr) {
    switch(opr) {
        case '+':
            // cout << l << opr << r << "=" << l+r << endl; 
            return l+r;
        case '-':
            // cout << l << opr << r << "=" << l-r << endl; 
            return l-r;
        case '*':
            // cout << l << opr << r << "=" << l*r << endl; 
            return l*r;
        case '/':
            // cout << l << opr << r << "=" << l/r << endl; 
            return l/r;
        default:
            return 0;
    }
}

bool Node::operator<(const Node a) const {
    return (value == '+' || value == '-') && (a.value == '*' || a.value == '/');
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
    postfix();
    return *this;
}
expretree& expretree::push(char v) {
    Node *newNode, *lc = prev;
    newNode = new Node(v, Operator, level);

    while(lc->parent != nullptr && newNode->level <= lc->parent->level) lc = lc->parent;
    while(lc->parent != nullptr && newNode->level == lc->parent->level && lc->tag == Operand) lc = lc->parent;
    // if(lc->tag == Operand || (lc->level == newNode->level && *lc >= *newNode) || (lc->level > newNode->level)) {
    if(lc->tag == Operand || *newNode <= *lc || newNode->level < lc->level) {
        // cout << "operator push 1" << endl;
        if(lc->parent != nullptr) {
            lc->parent->right = newNode;
            newNode->parent = lc->parent;
        }
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
    postfix();
    // system("pause");
    return *this;
}

void expretree::postfix_(Node* tmp) {
    if(tmp->left != nullptr) postfix_(tmp->left);
    if(tmp->right != nullptr) postfix_(tmp->right);
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
    if(tmp == root)
        cout << endl;
    return;
}

double expretree::calculate_(Node* tmp) {
    static stack<double> opd;
    if(tmp->left != nullptr) calculate_(tmp->left);
    if(tmp->right != nullptr) calculate_(tmp->right);
    double l,r;
    switch(tmp->tag) {
        case Operand:
            opd.push((double)tmp->value);
            // cout << opd.size() << " " << opd.top() << endl;
            break;
        case Operator:
            r = opd.top(); opd.pop();
            l = opd.top(); opd.pop();
            opd.push(cal(l,r,tmp->value));
            break;
        default:
            cout << "error" << endl;
            break;
    }
    if(tmp == root) {
        double result = opd.top();
        opd.pop();
        return result;
    }
    return 0;
    
}

