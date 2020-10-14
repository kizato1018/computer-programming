#include <bits/stdc++.h>

using namespace std;

double dis(pair<int, int> a, pair<int, int> b) {
    return sqrt(pow((a.first - b.first), 2) + pow((a.second - b.second), 2));
}

int main() {
    vector<pair<int, int> > v;
    int n, x, y;
    int cnt = 0;
    cin >> n;
    while(n--) {
        cin >> x >> y;
        v.push_back(pair<int, int>(x, y));
    }
    stable_sort(v.begin(), v.end(), [](pair<int, int> a, pair<int, int> b) { return dis(a, pair<int, int>(20000, 20000)) < dis(b, pair<int, int>(20000, 20000)); });
    for(auto i = v.begin(); i != v.end(); ) {
        for(auto j = v.begin(); j != v.end(); ++j) {
            if(i != j && dis(*i, *j) < 200) {
                ++cnt;
                break;
            }
        }
        v.erase(i);
    }
    cout << cnt << endl;
}