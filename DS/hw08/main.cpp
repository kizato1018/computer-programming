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

}

/*
040 020 060 010 030 050 070 045 055 052
*/