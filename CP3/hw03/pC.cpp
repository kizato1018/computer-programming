#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    int N;
    while(cin >> N) {
        int a[10005] = {0}, adj[10005] = {0};
        for(size_t i = 0; i < N; ++i)
            cin >> a[i];
        adjacent_difference(a, a+N, adj, [](int x, int y){return abs(x-y);});
        // for(int x = 1; x < N; ++x) {
        //     cout << adj[x] << " ";
        // }
        // puts("");
        bool num[10005] = {0};
        if(all_of(adj+1, adj+N, [N, &num](int x){ 
            if(x < 1 || x >= N) return false;
            // cout << x << ' ' << num[x] << '\n';
            if(num[x]) return false;
            return num[x] = true;}))
            cout << "Jolly" << endl;
        else 
            cout << "Not jolly" << endl;
        
    }
    
}