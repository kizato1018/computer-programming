#include <bits/stdc++.h>

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	while(cin >> n && n) {
		int num;
		while(cin >> num && num){
			int cnt = 1;
			stack<int> st;
			for(int i = 1; i <= n; i++) {
				st.push(i);
				while(num == st.top()) {
					st.pop();
					if(cnt++ < n) cin >> num;
					if(st.empty()) break;
				}
			}
			while(cnt++ < n) cin >> num;
			if(st.empty()) cout << "Yes" << endl;
			else cout << "No" << endl;
		}
	}
}
