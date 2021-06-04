#include <bits/stdc++.h>

using namespace std;

struct edge {
	int u, v, w;
}e[200010];

int root[100010];

void init(int num) {
	for(int i = 0; i < num; i++)
		root[i] = i;
}

int find(int x) {
	if(root[x] != x)
		return root[x] = find(root[x]);
	return x;
}

void unite(int a, int b) {
	a = find(a);
	b = find(b);
	if(a != b)
		root[a] = b;
}

bool cmp(edge a, edge b) {return a.w < b.w;}

int main() {
	int n, m;

	while(cin >> n >> m) {
		init(n);
		for(int i = 0; i < m; i++) {
			cin >> e[i].u >> e[i].v >> e[i].w;
		}

		sort(e, e + m, cmp);

		int cnt = 0;
		int64_t sum = 0;
		for(int i = 0; i < m; i++) {
			if(find(e[i].u) != find(e[i].v)) {
				cnt++;
				sum += e[i].w;
				unite(e[i].u, e[i].v);
			}
		}
		if(cnt != n - 1) cout << "-1" << endl;
		else cout << sum << endl;
	}
}