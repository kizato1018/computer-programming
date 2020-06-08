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
String String::operator + (const String& s) {
    String tmp(*this);
    std::cout << "tmp\n";
    return tmp += s;
    // String *ns = new String(*this);
    // (*ns).size_ += s.size_;
    // if((*ns).size_ > (*ns).capacity_) {
    //     (*ns).capacity_ <<= 1;
    // }
    // (*ns).str_ = new char [(*ns).capacity_];
    // strcpy((*ns).str_, str_);
    // strcat((*ns).str_, s.str_);
    // return *ns;
}
// String& String::operator + (const char* s) {
//     String *ns = new String(*this);
//     (*ns).size_ = size_ + strlen(s);
//     (*ns).capacity_ = capacity_;
//     if((*ns).size_ > (*ns).capacity_) (*ns).capacity_ <<= 1;
//     (*ns).str_ = new char [(*ns).capacity_];
//     strcpy((*ns).str_, str_);
//     strcat((*ns).str_, s);
//     return *ns;
// }
// String& String::operator + (char s) {
//     String *ns = new String(*this);
//     (*ns).size_ = size_ + 1;
//     if((*ns).size_ > (*ns).capacity_) {
//         (*ns).capacity_ <<= 1;
//         str_ = static_cast<char*>(realloc(str_, capacity_));
//     }
//     strcpy((*ns).str_, str_);
//     (*ns).str_[(*ns).size_ - 1] = s;
//     return *ns;    
// }
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



std::ostream& operator << (std::ostream& os, const String& s) {
    os << s.c_str();
    return os;
}