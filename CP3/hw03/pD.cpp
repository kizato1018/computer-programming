#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    int N;
    int cnt = 0;
    while(cin >> N && N > 0) {
        int a[10005] = {0}, result[10005] = {0};
        int h = 0;
        for(size_t i = 0; i < N; ++i)
            cin >> a[i];
        h = accumulate(a, a+N, 0) / N;
        if(cnt)
            puts("");
        cout << "Set #" << ++cnt << endl;
        cout << "The minimum number of moves is " << accumulate(a, a+N, 0, [h](int x, int y){return (y > h) ? x + y - h : x;}) << "." << endl;
        
    }
    
}
