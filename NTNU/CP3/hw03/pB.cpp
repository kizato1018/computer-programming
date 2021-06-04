#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    int T, N;
    cin >> T;
    for(size_t cnt = 1; cnt <= T; ++cnt) {
        int a[10005] = {0};
        int avg = 0;
        double per;
        cin >> N;
        for(size_t i = 0; i < N; ++i)
            cin >> a[i];
        avg = accumulate(begin(a), end(a), 0) / N;
        per = static_cast<double>(count_if(begin(a), end(a), [avg](int x){return x > avg;})) / N * 100;
        cout << fixed << setprecision(3) << per << "%" << endl;
    }
    
}