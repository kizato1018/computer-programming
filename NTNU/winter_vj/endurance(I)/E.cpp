#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	while(n--) {
		int score = 0;
		int cnt = 1;
		string s;
		cin >> s;
		for(int i = 0; i < s.length(); i++) {
			if(s[i] == 'O') score += cnt++;
			else cnt = 1;
		}
		cout << score << endl;
	}
}
