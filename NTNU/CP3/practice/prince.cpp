#include <iostream>
#include <string.h>
using namespace std;

class Attribute
{

// TODO: declare operator << as a friend
friend ostream & operator << (ostream &os, const Attribute &rhs);


public:

    // TODO: operator +=
    Attribute & operator += (const int num) {value_ += num; return *this;}
    // TODO: operator ==
    bool operator == (const Attribute & a) {return Value() == a.Value();}

    int Value() const {return value_;}
    void SetName(const char name[]) { strcpy(name_, name); }
    const char *Name() const { return name_; }
private:
    char name_[30] = {};
    int value_ = 0;
};

ostream & operator << (ostream &os, const Attribute &rhs)
{
    os << rhs.name_ << ' ' << rhs.value_;
    return os;
}


class Princess
{
public:
    // TODO: operator []
    Attribute & operator [] (const char attr_name[]);

private:
    static const std::size_t MaxNumAttr = 10;
    Attribute attributes_[MaxNumAttr];
    std::size_t num_attr_ = 0;
};

Attribute & Princess::operator[](const char attr_name[])
{
    // TODO:
    // search for attr_name, if found, return the Attribute object by reference;
    // otherwise, if size enough, add one Attribute object and return it by reference;
    // now we do not deal with the case in which adding a new Attrubute fails
    for(std::size_t i = 0; i < num_attr_; ++i) {
            if(strcmp(attr_name, attributes_[i].Name()) == 0) {
                return attributes_[i];
            }
        }
    if(num_attr_ < MaxNumAttr) {
        attributes_[num_attr_].SetName(attr_name);
        num_attr_ += 1;
        return attributes_[num_attr_-1];
    }
}

int main()
{
    Princess princess;

    princess["Intelligence"] += 10;
    cout << princess["Intelligence"] << endl;

    princess["Intelligence"] += 30;
    princess["Magic"] += 40;

    if (princess["Intelligence"] == princess["Magic"])
    {
        cout << "Equal" << endl;
    }
}