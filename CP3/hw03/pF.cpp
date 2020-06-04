#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int N = 0;
    cin >> N;
    cout << "Lumberjacks:" << endl;
    while(N) {
        int a[10] = {0};
        for(int i = 0; i < 10; ++i)
            cin >> a[i];
        if(is_sorted(begin(a), end(a)) || is_sorted(begin(a), end(a), greater<int>())) {
            cout << "Ordered" << endl;
        }
        else 
            cout << "Unordered" << endl;
        --N;
    }
}