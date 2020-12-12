#ifndef __BINTREE_H__
#define __BINTREE_H__

enum Tag{Operand, Operator};
class Node {
public:
    Node() {}
    Node(Tag t) : tag(t) {}
    Node(int value, Tag t, int level) : value(value), tag(t), level(level) {}
    bool isFull() { return left != nullptr & right != nullptr; }
    bool operator < (const Node) const;
    bool operator > (const Node a) const {return a < *this;}
    bool operator <= (const Node a) const {return !(*this > a);}
    bool operator >= (const Node a) const {return !(*this < a);}
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
    void postfix() { postfix_(root); }
    double calculate() { return calculate_(root); }
    int level = 0;
    expretree& push(int);
    expretree& push(char);
private:
    void postfix_(Node*);
    double calculate_(Node*);
    // Node* NewNode(char);
    // Node* NewNode(int);
    // int Getpriority(Node);
    Node *root = nullptr;
    Node *prev = nullptr;
};



#endif