#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

class T{
public:
    void print() const {cout << _text << endl;}
    void set(const string text) {_text = text;}
private:
    string _text;
};

void f(const T &t) {
    t.print();
}

int main() {
    T t;
    t.set("Hello");
    t.print();
    f(t);
}