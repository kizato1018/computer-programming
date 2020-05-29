#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int T, N;
    cin >> T;
    for(size_t cnt = 1; cnt <= T; ++cnt) {
        int a[105] = {0};
        cin >> N;
        for(size_t i = 0; i < N; ++i)
            cin >> a[i];
        cout << "Case " << cnt << ": " << *max_element(begin(a), end(a)) << endl;
    }
    
}