#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

int main() {
    int N;
    while(cin >> N && N) {
        string s;
        int ln;
        cin >> s;
        ln = s.size() / N;
        for(int i = 0; i < N; ++i) {
            reverse(s.begin()+(i*ln), s.begin()+((i+1)*ln));
        }
        cout << s << endl;
    }
}