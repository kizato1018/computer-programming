#ifndef __MYSTRING_H__
#define __MYSTRING_H__
#include <iostream>

typedef unsigned long size_t;
class String {
public:
    String()=default;
    String(const String&);
    String(const char*);
    ~String()=default; // {std::cout << str_ << " destruction\n";}
    size_t size() const;
    size_t capacity() const;
    const char* c_str() const;
    const char& operator[](size_t) const;
    char& operator [] (size_t);
    String& operator = (const String&);
    String& operator = (const char*);
    String& operator = (char);
    String& operator += (const String&);
    String& operator += (const char*);
    String& operator += (char);
    String operator + (const String&);
    String operator + (const char*);
    String operator + (const char);
    void clear();
    void swap(String&);
    friend bool operator == (const String&, const String&);
    friend bool operator == (const char*, const String&);
    friend bool operator == (const String&, const char*);
    friend bool operator != (const String&, const String&);
    friend bool operator != (const char*, const String&);
    friend bool operator != (const String&, const char*);
    friend bool operator < (const String&, const String&);
    friend bool operator < (const char*, const String&);
    friend bool operator < (const String&, const char*);
    friend bool operator <= (const String&, const String&);
    friend bool operator <= (const char*, const String&);
    friend bool operator <= (const String&, const char*);
    friend bool operator > (const String&, const String&);
    friend bool operator > (const char*, const String&);
    friend bool operator > (const String&, const char*);
    friend bool operator >= (const String&, const String&);
    friend bool operator >= (const char*, const String&);
    friend bool operator >= (const String&, const char*);
    friend std::ostream& operator << (std::ostream&, const String&);
private:
    char *str_ = nullptr;
    size_t size_ = 0, capacity_ = 0;
};

#endif