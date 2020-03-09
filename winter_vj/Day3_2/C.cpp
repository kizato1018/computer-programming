#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	while(cin >> n) {
		map<string, int> m;
		string s;
		getline(cin, s);
		while(n--) {
			string tmp;
			getline(cin, s);
			tmp.assign(s, 0, s.find(' '));
			m[tmp]++;
		}
		for(map<string,int>::iterator it = m.begin(); it != m.end(); it++) {
			cout << it->first << " " << it->second << endl;
		}
	}
}
