#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int N, Q, cnt = 0;
    while(cin >> N >> Q && N && Q) {
        cout << "CASE# " << ++cnt << ":" << endl;
        int a[100005] = {0}, b;
        int *pos;
        for(size_t i = 0; i < N; ++i)
            cin >> a[i];
        sort(a, a+N);
        for(size_t i = 0; i < Q; ++i) {
            cin >> b;
            pos = lower_bound(a, a+N, b);
            if(pos != a+N && *pos == b) 
                cout << b << " found at " << pos-a+1 << endl;
            else 
                cout << b << " not found" << endl;
        }
            
    }
}