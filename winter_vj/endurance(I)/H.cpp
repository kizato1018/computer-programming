#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	while(n--) {
		string s;
		int v = 0;
		int num = 0;
		cin >> s;
		for(int i = 0; i < 3; i++)
			v += (s[i] - 'A') * pow(26, 2-i);
		for(int i = 4; i < 8; i++) {
			num *= 10;
			num += s[i] - '0';
		}
		v = abs(v - num);
		if(v <= 100) cout << "nice" << endl;
		else cout << "not nice" << endl;
	}
}
