#include <iostream>
#include <string.h>
#include <array>
using namespace std;

struct CStudent
{
   int id = 0,
       score = 0;
   char name[30] = {};
};

ostream & operator << (ostream &os, const CStudent &stu)
{
    os << stu.id << ' ' << stu.name << ' ' << stu.score;
    return os;
}

void sort(CStudent data[], int n, /* TODO */int (*cmp)(const CStudent &, const CStudent &))
{
   // Call cmp(data[i], data[j]) when you need to compare two CStudent objects
   for(int i = 0; i < n; ++i) {
       for(int j = 1; j < n-i; j++) {
           if(cmp(data[j-1], data[j]) > 0) {
               swap(data[j-1], data[j]);
           }
       }
   }
}

/* TODO */
int CompareId(const CStudent &lhs, const CStudent &rhs) {
    return lhs.id - rhs.id;
}
int CompareName(const CStudent &lhs, const CStudent &rhs) {
    return strcmp(lhs.name, rhs.name);
}
int CompareScore(const CStudent &lhs, const CStudent &rhs) {
    return lhs.score - rhs.score;
}



int main()
{
    CStudent data[] = {{1, 90, "David"}, {5, 100, "Allen"}, {3, 92, "Alice"}, {2, 85, "Bob"}, {4, 91, "Cyndi"}};
    const int Size = sizeof(data)/sizeof(data[0]);

    sort(data, Size, CompareId);
    for (const auto &e: data) {cout << e << endl;} cout << endl;
    sort(data, Size, CompareName);
    for (const auto &e: data) {cout << e << endl;} cout << endl;
    sort(data, Size, CompareScore);
    for (const auto &e: data) {cout << e << endl;} cout << endl;
}





