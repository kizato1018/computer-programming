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

int main() {
    String s("Hello"), t(s), u;
    u = s;
    cout << s << endl;
    cout << t << endl;
    cout << u[0] << endl;
}