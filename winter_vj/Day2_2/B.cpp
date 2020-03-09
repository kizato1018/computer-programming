#include <bits/stdc++.h>

using namespace std;

int main() {
	int n, m, I, J;

	while(cin >> n >> m && n + m) {

		bool G[110][110] = {false};
		int in[110] = {0};
		for(int i = 0; i < m; i++) {
			cin >> I >> J;
			G[I][J] = true;
			in[J]++;
		}

		queue<int> q;
		for(int i = 1; i <= n; i++) {
			if(in[i] == 0) q.push(i);
		}

		vector<int> ans;
		while(!q.empty()) {
			int t = q.front();
			q.pop();
			ans.push_back(t);

			for(int i = 1; i <= n; i++) {
				if(G[t][i]) {
					in[i]--;
					if(in[i] == 0)
						q.push(i);
				}
			}
		}

		for(int i = 0 ; i < ans.size(); i++) {
			cout << ans[i] << " \n"[i == ans.size() - 1];
		}
	}
}