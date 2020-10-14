#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

int main() {
    vector<int> v = {1,2,3,4,5};
    for(auto i = v.begin(), *(i+1) != v.end(); ++i);
}