#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

string& New_S(const char* cs) {
    string *s = new string(cs);
    cout << *s << endl;
    return *s;
}

class S {
public:
    S(){};
    S(const S &s)=default;
    void show() {cout << str << endl;}
    string str;
};

int main() {
    string a("It is time to write a long sentence! "), b("apple"), c;
    // printf("%p\n%p\n%p\n", &a, &b, &(a+b));
    cout << string("Hello").size();
    
}