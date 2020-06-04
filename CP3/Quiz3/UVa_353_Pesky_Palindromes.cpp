#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool isPalindrome(const string &s) {
    string r = s;
    reverse(r.begin(), r.end());
    return s == r;
}

int main() {
    string s;
    while(cin >> s) {
        vector<string> v;
        int cnt = 0;
        for(size_t ln = 1; ln <= s.size(); ++ln) {
            for(size_t pos = 0; pos+ln <= s.size(); ++pos) {
                v.push_back(s.substr(pos, ln));
            }
        }
        sort(v.begin(), v.end());
        v.resize(distance(v.begin(), unique(v.begin(), v.end())));
        for(auto i : v) {
            if(isPalindrome(i)) {
                ++cnt;
                // cout << i << " " << cnt << ", ";
            }
        }
        cout << "The string '" << s << "' contains " << cnt << " palindromes." << endl;
    }
}