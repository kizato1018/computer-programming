#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    string a, b;
    while(cin >> a >> b) {
        auto begin = b.begin();
        size_t i;
        for(i = 0; i < a.size(); ++i) {
            begin = find(begin, b.end(), a[i]);
            if(begin == b.end())
                break;
            ++begin;
        }
        if(i == a.size())
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
}

