#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int N, Q, cnt = 0;
    while(cin >> N >> Q && N && Q) {
        cout << "CASE# " << ++cnt << ":" << endl;
        int a[1005] = {0}, b;
        int *pos;
        for(size_t i = 0; i < N; ++i)
            cin >> a[i];
        sort(begin(a), end(a), greater<int>());
        for(size_t i = 0; i < Q; ++i) {
            cin >> b;
            pos = lower_bound(begin(a), end(a), b);
            if(pos != end(a)) 
                cout << b << " found at " << pos-begin(a) << endl;
            else 
                cout << b << "not found" << endl;
        }
            
    }
}