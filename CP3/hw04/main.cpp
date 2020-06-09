#include <iostream>
#include "String.h"

using namespace std;

void Constructors() {
    cout << "Constructors:" << endl;
    String s, t("CSIE108"), u(t);
    cout << s << endl;
    cout << t << endl;
    cout << u << endl;
    cout << endl;
}

void Copy() {
    cout << "Copy assignment:" << endl;
    String s1("NTU"), t1("NTNU");
    s1 = t1;
    cout << s1 << endl;
    cout << t1 << endl;
    cout << endl;
}

void Size_C_str() {
    cout << "size() and c_str():" << endl;
    String s("NTNU");
    cout << s.size() << endl; // 4
    const char *p = s.c_str();
    cout << p << endl;
    cout << endl;
}

void ReadWrite(String &str) {
    cout << "ReadWrite ";
    str[2] = 'T';
    cout << str << endl;
}
void ReadOnly(const String &str) {
    cout << "ReadOnly ";
    char c = str[1];
    cout << c << endl;
}
void RW() {
    cout << "operator []: " << endl;
    String s("NTNU");
    ReadWrite(s);
    ReadOnly(s);
    cout << endl;
}

void PlusE() {
    cout << "operator +=:" << endl;
    String s("NT"), t("NU");
    s += t;
    cout << s << endl;
    cout << endl;
}

void Plus() {
    cout << "operator +:" << endl;
    String s("NT"), t("NU"), u;
    u = s + t;
    cout << u << endl;
    cout << endl;
}

void Clear() {
    cout << "clear():" << endl;
    String s("NT");
    s.clear();
    cout << s << endl;
    cout << endl;
}

void Swap() {
    cout << "swap():" << endl;
    String s("NTNU"), u("NTU");
    cout << "before: " << s << "," << u << endl;
    s.swap(u);
    cout << "after: " << s << "," << u << endl;
    cout << endl;
}

int main() {
    Constructors();
    Copy();
    Size_C_str();
    RW();
    PlusE();
    Plus();
    Clear();
    Swap();
}