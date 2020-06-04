#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int N;
    string s;
    string Min;
    cin >> N;
    while(N) {
        cin >> s;
        Min = s;
        for(size_t i = 1; i < s.size(); ++i) {
            rotate(s.begin(), s.begin()+1, s.end());
            Min = min(Min, s);
        }
        cout << Min << endl;;
        --N;
    }
}