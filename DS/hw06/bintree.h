#ifndef __BINTREE_H__
#define __BINTREE_H__

enum Tag{Operand, Operator};
class Node {
public:
    Node() {}
    Node(Tag t) : tag(t) {}
    Node(int value, Tag t, int level) : value(value), tag(t), level(level) {}
    bool isFull() { return left != nullptr & right != nullptr; }
    bool operator < (const Node);
    bool operator >= (const Node);
    friend class expretree;
private:
    Tag tag; 
    int value = 0;
    int level = 0;
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
};

class expretree {
public:
    expretree() {}
    void postfix() {postfix(root);}
    int level = 0;
    expretree& push(int);
    expretree& push(char);
private:
    void postfix(Node*);
    // Node* NewNode(char);
    // Node* NewNode(int);
    int Getpriority(Node);
    Node *root = nullptr;
    Node *prev = nullptr;
};



#endif