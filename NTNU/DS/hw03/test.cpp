#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

int main() {
    vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    vector <int> x;
    x = v;
    for(auto i = x.begin(); i != x.end(); ++i) {
        if(*i == 3) {
            x.push_back(11);
            i = x.begin()+2;
        }
        cout << *i << " ";
    }
}