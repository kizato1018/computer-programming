#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include "BST.h"

using namespace std;

struct Product {
    Product() {}
    Product(int n) : product_number(n) {}
    Product(int n, int p, int a) : product_number(n), price(p), amount(a) {}
    int product_number;
    int price;
    int amount;
    bool operator < (const Product a) const {return product_number < a.product_number;}
    bool operator <= (const Product a) const {return product_number <= a.product_number;}
    bool operator > (const Product a) const {return product_number > a.product_number;}
    bool operator >= (const Product a) const {return product_number >= a.product_number;}
    bool operator == (const Product a) const {return product_number == a.product_number;}
    bool operator != (const Product a) const {return product_number != a.product_number;}
    Product operator + (const Product a) const {return Product(product_number, price, amount + a.amount);}
    Product operator - (const Product a) const {return Product(product_number, price, amount - a.amount);}
    friend istream& operator >> (istream& in, Product& a) {
        in >> a.product_number >> a.price >> a.amount;
        return in;
    }
    friend ostream& operator << (ostream& out, Product& a) {
        out << setw(3) << setfill('0') << a.product_number << " " << a.price << " " << a.amount;
        return out; 
    };
    void Show() const {cout << "Product number: " << setw(3) << setfill('0') << product_number << "\nprice: " << price << "\namount: " << amount << endl;}
    void Showln() const {cout << "Product number: " << setw(3) << setfill('0') << product_number << ", price: " << price << ", amount: " << amount << "." << endl;}
    bool Check() const {
        if(product_number < 0 || product_number > 999) {
            cout << "unvalid product number." << endl;
            return false;
        }
        if(price < 0) {
            cout << "unvalid product price." << endl;
            return false;
        }
        if(amount < 0) {
            cout << "unvalid amount." << endl;
            return false;
        }
        return true;
    }
};

bool init(BST<Product>& Tree) {
    string filename;
    cout << "enter input filename: ";
    cin >> filename;
    Product item;
    ifstream in;
    in.open(filename);
    if(!in) {
        cerr << "File open failed." << endl;
        return false;
    }
    while(in >> item) {
        // cout << item << endl;
        item.Show();
        Tree.Push(item);
    }
    in.close();
    return true;
}

bool Search(BST<Product>& Tree) {
    Product target;
    cout << "enter product number: ";
    cin >> target.product_number;
    Node<Product> *tmp = Tree.Find(target);
    char c;
    if(tmp == nullptr) {
        cout << "Product not found." << endl;
        return false;
    }
    while(tmp) {
        tmp->value.Show();
        c = getch();
        if(c == 'R') return true;
        else if(c == 'N') {
            tmp = Tree.Successor(tmp);
        }
    }
    return true;
}

bool Import(BST<Product>& Tree) {
    Product target;
    Node<Product>* node;
    cout << "enter product number: ";
    cin >> target.product_number;
    if(!target.Check()) return false;
    if(!(node = Tree.Find(target))) {
        cout << "enter product price: ";
        cin >> target.price;
        if(!target.Check()) return false;
        cout << "enter product amount: ";
        cin >> target.amount;
        if(!target.Check()) return false;
        Tree.Push(target);
    }
    else {
        cout << "enter product amount: ";
        cin >> target.amount;
        if(!target.Check()) return false;
        node->value = node->value + target;
        target = node->value;
    }
    cout << "=== you have inserted: ===" << endl;
    target.Show();
    cout << "=== into the tree ===" << endl;
    return true;
}

bool Delete(BST<Product>& Tree) {
    Product target;
    Node<Product>* node;
    cout << "enter product number: ";
    cin >> target.product_number;
    if(!(node = Tree.Find(target))) {
        cout << "The product you want to delete is not exists in database." << endl;
        return false;
    }
    target = node->value;
    Tree.Delete(target);
    cout << "=== you have just deleted:===" << endl;
    target.Show();
    return true;
}

bool Export(BST<Product>& Tree) {
    Product target;
    Node<Product>* node;
    cout << "enter product number: ";
    cin >> target.product_number;
    if(!target.Check()) return false;
    if(!(node = Tree.Find(target))) {
        cout << "The product you want to export is not exists in database." << endl;
        return false;
    }
    else {
        cout << "enter product amount: ";
        cin >> target.amount;
        if(!target.Check()) return false;
        if(node->value.amount < target.amount) {
            cout << "The product you want to export is notenoughin database." << endl;
            return false;
        }
        target = node->value;
        cout << "=== you have justexport:===" << endl;
        target.Show();
        node->value = node->value - target;
        target = node->value;
        cout << "===remains: ===" << endl;
        target.Show();
    }
    return true;
}

void List(BST<Product>& Tree) {
    Node<Product>** arr = Tree.Infix();
    for(int i = 0; i < Tree.Size(); ++i) {
        arr[i]->value.Showln();
    }
    delete arr;
}

bool Modify(BST<Product>& Tree) {
    Product Old, New;
    Node<Product>* node;
    cout << "enter product number: ";
    cin >> Old.product_number;
    cout << "enter new product number: ";
    cin >> New.product_number;
    if(!Old.Check()) return false;
    if(!(node = Tree.Find(Old))) {
        cout << "Product not found. Modify falied." << endl;
        return false;
    }
    else {
        New = node->value;
        Tree.Delete(node);
        Tree.Push(New);
        return true;
    }
}

Product Search_price(BST<Product>& Tree) {
    Node<Product>** arr = Tree.BFS();
    Product max(-1, -1, -1);
    for(int i = 0; i < Tree.Size(); ++i) {
        if(max.price < arr[i]->value.price)
            max = arr[i]->value;
    }
    cout << "highest price product:" << max;
    delete arr;
    return max;
}

bool Save(BST<Product>& Tree) {
    Node<Product>** arr = Tree.BFS();
    string filename;
    ofstream out;
    cout << "enter output filename: ";
    cin >> filename;
    out.open(filename);
    if(!out) {
        cout << "File open failed." << endl;
        return false;
    }
    for(int i = 0; i < Tree.Size(); ++i) {
        out << arr[i]->value << endl;
    }
    out.close();
    delete arr;
    return true;
}

int main() {
    BST<Product> Tree;
    if(!init(Tree)) return -1;
    int option;
    while(1) {
        cout << "1) Search" << endl;
        cout << "2) Import" << endl;
        cout << "3) Delete" << endl;
        cout << "4) Export" << endl;
        cout << "5) List" << endl;
        cout << "6) Modify" << endl;
        cout << "7) Search highest price" << endl;
        cout << "8) Save" << endl;
        cout << "0) Exit" << endl;
        cin >> option;
        switch (option)
        {
        case 1:
            Search(Tree);
            break;
        case 2:
            Import(Tree);
            break;
        case 3:
            Delete(Tree);
            break;
        case 4:
            Export(Tree);
            break;
        case 5:
            List(Tree);
            break;
        case 6:
            Modify(Tree);
            break;
        case 7:
            Search_price(Tree);
            break;
        case 8:
            Save(Tree);
            break;
        case 0:
            return 0;
        
        default:
            cout << "Wrong option" << endl;
            break;
        }
        system("pause");
        system("cls");
    }



}

/*
040 020 060 010 030 050 070 045 055 052
*/