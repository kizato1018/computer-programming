#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

// bool cmp(string a, string b) {
//     return
// }

int main() {
    string s, s2[100] = {};
    vector<string> vs;
    map<string, int> m;
    int cnt = 0;
    while(cin >> s && s != "#") {
        s2[cnt] = s;
        for_each(s.begin(), s.end(), [](char &c){c = toupper(c);});
        sort(s.begin(), s.end());
        if(m.count(s) == 0) m[s] = 1;
        else ++m[s];
        ++cnt;
    }
    
    for(int i = 0; i < cnt; ++i) {
        s = s2[i];
        for_each(s.begin(), s.end(), [](char &c){c = toupper(c);});
        sort(s.begin(), s.end());
        if(m[s] == 1)
            vs.push_back(s2[i]);
    }
    sort(vs.begin(), vs.end());
    for(auto i : vs)
        cout << i << endl;
}