#include <bits/stdc++.h>

using namespace std;

int main() {
    vector <int> v = {1,2,3,4,5,6,7,8,9,10};
    v[v.size()+1] = 11;
    for(auto a : v)
        cout << a << " ";

}