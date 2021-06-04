#include <bits/stdc++.h>

using namespace std;

int main() {
	string s1, s2;
	while(getline(cin, s1) && getline(cin, s2)) {
		int DP[1010][1010] = {0};
		for(int i = 1; i <= s1.length(); i++) {
			for(int j = 1; j <= s2.length(); j++) {
				if(s1[i-1] == s2[j-1])
					DP[i][j] = DP[i-1][j-1]+1;
				else
					DP[i][j] = max(DP[i-1][j], DP[i][j-1]);
			}
		}
		cout << DP[s1.length()][s2.length()] << endl;
	}
}
