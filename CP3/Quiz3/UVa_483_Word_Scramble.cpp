#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

int main() {
    string s;
    stringstream ss;
    while(getline(cin, s)) {
        ss << s;
        while(ss >> s) {
            reverse(s.begin(), s.end());
            cout << s;
        }
        cout 
    }
}