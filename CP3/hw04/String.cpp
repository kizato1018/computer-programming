#include <cstring>
#include <cstdlib>
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

String::String(const String &s):size_(s.size_), capacity_(s.capacity_) {
    str_ = new char[capacity_];
    strcpy(str_, s.str_);
};
String::String(const char *s):size_(strlen(s)), capacity_((size_ > 15) ? size_ : 15) {
    str_ = new char[capacity_];
    strcpy(str_, s);
};
size_t String::size() const { return size_; }
size_t String::capacity() const { return capacity_;}
const char* String::c_str() const { return str_; }
const char& String::operator[](size_t i) const { return str_[i]; }
char& String::operator [] (size_t i) { const_cast<char &> (static_cast<const String &>(*this)[i]);}
String& String::operator = (const String& s) { 
    size_ = s.size_;
    if(capacity_ < s.capacity_) {
        capacity_ = s.capacity_;
        delete str_;
        str_ = new char [capacity_];
    }
    strcpy(str_, s.str_);
    return *this;
}
String& String::operator = (const char* s) { 
    size_ = strlen(s);
    if(capacity_ < size_) {
        capacity_ = size_;
        delete str_;
        str_ = new char [capacity_];
    }
    strcpy(str_, s);    
    return *this;
}
String& String::operator = (char c) { 
    char s[] = " ";
    s[0] = c;
    strcpy(str_, s);    
    return *this;
}
String& String::operator += (const String& s) {
    size_ += s.size_;
    if(size_ > capacity_) {
        capacity_ <<= 1;
        str_ = (char *)realloc(str_, capacity_);
    }
    strcat(str_, s.str_);
    return *this;
}
String& String::operator += (const char* s) {
    size_ += strlen(s);
    if(size_ > capacity_) {
        capacity_ <<= 1;
        str_ = (char *)realloc(str_, capacity_);
    }
    strcat(str_, s);
    return *this;
}
String& String::operator += (char s) {
    size_ = size_ + 1;
    if(size_ > capacity_) {
        capacity_ <<= 1;
        str_ = (char *)realloc(str_, capacity_);
    }
    str_[size_ - 1] = s;
    return *this;
}
String String::operator + (const String& s) {
    String tmp(*this);
    return tmp += s;
}
String String::operator + (const char* s) {
    String tmp(*this);
    return tmp += s;
}
String String::operator + (char s) {
    String tmp(*this);
    return tmp += s;
}
void String::clear() {
    size_ = 0;
    delete str_;
}
void String::swap(String& s) {
    String tmp;
    tmp.size_ = size_;
    tmp.capacity_ = capacity_;
    tmp.str_ = str_;
    size_ = s.size_;
    capacity_ = s.capacity_;
    str_ = s.str_;
    s.size_ = tmp.size_;
    s.capacity_ = tmp.capacity_;
    s.str_ = tmp.str_;
}
bool operator == (const String& lhs, const String& rhs) { return strcmp(lhs.str_, rhs.str_) == 0;}
bool operator == (const char* lhs, const String& rhs) { return strcmp(lhs.str_, rhs.str_) == 0;}
bool operator == (const String& lhs, const char* rhs) { return strcmp(lhs.str_, rhs.str_) == 0;}
bool operator != (const String& lhs, const String& rhs);
bool operator != (const char* lhs, const String& rhs);
bool operator != (const String& lhs, const char* rhs);
bool operator < (const String& lhs, const String& rhs);
bool operator < (const char* lhs, const String& rhs);
bool operator < (const String& lhs, const char* rhs);
bool operator <= (const String& lhs, const String& rhs);
bool operator <= (const char* lhs, const String& rhs);
bool operator <= (const String& lhs, const char* rhs);
bool operator > (const String& lhs, const String& rhs);
bool operator > (const char* lhs, const String& rhs);
bool operator > (const String& lhs, const char* rhs);
bool operator >= (const String& lhs, const String& rhs);
bool operator >= (const char* lhs, const String& rhs);
bool operator >= (const String& lhs, const char* rhs);

std::ostream& operator << (std::ostream& os, const String& s) {
    os << s.c_str();
    return os;
}