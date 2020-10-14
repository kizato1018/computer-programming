#include <bits/stdc++.h>

using namespace std;

int main() {
    vector <int> v = {1,2,3,4,5,6,7,8,9,10};
    for(auto i = v.begin(); i != v.end(); ++i) {
        for(auto j = v.begin(); j != v.end(); ++j) {
            if(*i + *j == 7) {
                v.erase(i);
                break;
            }
        }
        printf("i = %d\n", *i);
        for(auto j : v) {
            printf("%d ", j);
        }
        puts("");
    }

}