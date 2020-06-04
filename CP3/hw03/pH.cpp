#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    int T;
    cin >> T;
    while(T) {
        int N;
        int a[10005] = {0};
        int mid;
        cin >> N;
        for(size_t i = 0; i < N; ++i) 
            cin >> a[i];
        nth_element(a, a+N/2, a+N);
        mid = a[N/2];
        cout << accumulate(a, a+N, 0, [mid](int x, int y) {return x + abs(mid - y);}) << endl;
        --T;
    }
}