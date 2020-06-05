#ifndef __MYSTRING_H__
#define __MYSTRING_H__
#include <iostream>

typedef unsigned long size_t;
class String {
public:
    String();
    String(const String&);
    String(const char*);
    ~String() = default;
    size_t size() const;
    const char* c_str() const;
    const char& operator[](size_t) const;
    char& operator [] (size_t);
    String& operator += (const String&);
    String& operator += (const char*);
    String& operator += (char);
    void clear();
    String& operator = (const String&);
    String& operator = (const char*);
    String& operator = (char);
    void swap(String &);
    friend std::ostream& operator << (std::ostream&, const String&);
private:
    char *str_ = nullptr;
    size_t size_ = 0, capacity_ = 0;
};

#endif