#include <iostream>

using namespace std;

int main() {
    string s1("123456");
    for(auto i = s1.rbegin(); i != s1.rend(); ++i) {
        cout << *i;
    }
}