#include <iostream>
#include <fstream>
#include <iomanip>
#include "BST.h"

using namespace std;

struct Product {
    Product() {}
    Product(int n) : product_number(n) {}
    int product_number;
    int price;
    int amount;
    bool operator < (const Product a) const {return product_number < a.product_number;}
    bool operator == (const Product a) const {return product_number == a.product_number;}
    bool operator != (const Product a) const {return !(*this == a);}
    friend istream& operator >> (istream& in, Product& a) {
        in >> a.product_number >> a.price >> a.amount;
        return in;
    }
    friend ostream& operator << (ostream& out, Product& a) {
        out << "Product(" << setw(3) << setfill('0') << a.product_number << ") $" << a.price << " x" << a.amount;
        return out; 
    };

};

int main() {
    BST<Product> Tree;
    Product item;
    ifstream in;
    string filename;
    int x;
    cin >> filename;
    in.open(filename);
    if(!in) {
        cerr << "file open failed." << endl;
        return -1;
    }
    while(in >> item) {
        Tree.Push(item);
        cout << item << endl;
    }
    cout << endl;
    Tree.Show();
    Product* t;
    bool flag = false;
    cin >> x;
    cout << "Increase" << endl;
    while(t = Tree.Increase_order(Product(x))) {
        flag = true;
        cout << *t << endl;
    }
    if(!flag)
        cout << "Not Found" << endl;
    // BST<int> B;
    // int x;
    // for(int i = 0 ; i < 10; ++i) {
    //     cin >> x;
    //     B.Push(x);
    // }
    // cout << endl;

    // B.Show();
    // cin >> x;
    // B.Delete(x);
    // B.Show();

    // Node<int>* f = B.Find(x);
    // int v, p, l, r;
    // v = (f) ? f->value : -1;
    // p = (f->parent) ? f->parent->value : -1;
    // l = (f->left) ? f->left->value : -1;
    // r = (f->right) ? f->right->value : -1;
    // printf("%d P:%d L:%d R:%d\n", v, p, l, r);

}

/*
040 020 060 010 030 050 070 045 055 052

星期 早上 (8~11)
星期 中午 (11~14)
星期 下午 (14~18)
星期 晚上 (18~21)
*/