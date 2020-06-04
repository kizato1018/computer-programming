#include <iostream>
#include <cctype>

using namespace std;

int main() {
    string s;
    int cnt = 0;
    bool flag;
    while(getline(cin, s)) {
        cnt = 0;
        for(size_t i = 0; i < s.size(); ++i) {
            if(isalpha(s[i])) {
                flag = true;
            }
            else {
                if(flag) 
                    ++cnt;
                flag = false;
            }
        }
        cout << cnt << endl;
    }
}