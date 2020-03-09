#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	string s;
	while(cin >> s) {
		list<char> l;
		list<char>::iterator it = l.begin();
		for(int i = 0; i < s.length(); i++) {
			if(s[i] == '[') it = l.begin();
			else if(s[i] == ']') it = l.end();
			else l.insert(it, s[i]);
		}
		for(it = l.begin(); it != l.end(); it++)
			cout << *it;
		cout << endl;
	}
}
