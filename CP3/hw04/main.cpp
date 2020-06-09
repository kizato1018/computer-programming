#include <iostream>
#include "String.h"

using namespace std;

// class String {
// public:
//     String();
//     String(const String&);
//     String(const char*);
//     // ~String();
//     size_t size() const;
//     const char* c_str() const;
//     const char& operator[](size_t) const;
//     char& operator [] (size_t);
//     String& operator += (const String&);
//     String& operator += (const char*);
//     String& operator += (char);
//     void clear();
//     String& operator = (const String&);
//     String& operator = (const char*);
//     String& operator = (char);
//     void swap(String &);
//     friend ostream& operator << (ostream& os, const String s);
// private:
//     char *str_ = nullptr;
//     size_t size_ = 0, capacity_ = 0;
// };

// String::String() = default;
// String::String(const String &s):str_(s.str_) {};
// String::String(const char *s):str_(const_cast<char *>(s)) {};


// std::ostream& operator << (std::ostream& os, const String s) {
//     os << s.c_str();
//     return os;
// }

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

int main() {
    String s("NTNU"), t("GOOD"), u;
    // cout << s.size() << endl;
    // const char *p = s.c_str();
    // cout << p << endl;
    // ReadWrite(s);
    // ReadOnly(s);
    // u = s+t;
    
    // cout << s+t << endl;
    cout << "Hello" << endl;
    // cout << u << " " << u.size() << " " << u.capacity() << endl;
    // u.clear();
    // cout << u << " " << u.size() << " " << u.capacity() << endl;

    cout << "end\n";
    String a("It is time to write a long sentence! "), b("apple is really good"), c;
    printf("%p %p\n", (a.c_str()), (b.c_str()));
     cout << a << " " << a.size() << " " << a.capacity() << endl;
    swap(a, b);
    // c = a;
    printf("%p %p\n", (a.c_str()), (b.c_str()));
     cout << a << " " << a.size() << " " << a.capacity() << endl;

}