#include <iostream>
#include <cstdio>
#include <list>

using namespace std;

int main() {
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    printf("%p\n", &l.front());
}