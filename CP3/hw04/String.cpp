#include "String.h"

// class String {
// public:
//     String();
//     String(const String &s):str_(s.str_) {};
//     String(const char *s):str_(const_cast<char *>(s)) {};
//     ~String();
//     size_t size() const;
//     const char* c_str() const;
//     const char& operator[](size_t i) const;
//     char& operator [] (size_t i);
//     String& operator += (const String&);
//     String& operator += (const char*);
//     String& operator += (char);
//     void clear();
//     String& operator = (const String&);
//     String& operator = (const char*);
//     String& operator = (char);
//     void swap(String &);
//     friend std::ostream& operator << (std::ostream& os, const String &);
// private:
//     char *str_ = nullptr;
//     size_t size_ = 0, capacity_ = 0;
// };

String::String() = default;
String::String(const String &s):str_(s.str_) {};
String::String(const char *s):str_(const_cast<char *>(s)) {};
size_t String::size() const { return size_; }
const char* String::c_str() const { return str_; }
const char& String::operator[](size_t i) const { return str_[i]; }
char& String::operator [] (size_t i) { const_cast<char &> (static_cast<const String &>(*this)[i]);}
String& String::operator += (const String&) {
    
}
String& String::operator += (const char*);
String& String::operator += (char);

String& String::operator = (const String& s) { 
    delete str_;
    str_ = s.str_;
    size_ = s.size_;
    capacity_ = s.capacity_;
    return *this;
}


std::ostream& operator << (std::ostream& os, const String& s) {
    os << s.c_str();
    return os;
}