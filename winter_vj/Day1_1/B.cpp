#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	while(n > 0) {
		int num;
		priority_queue<int, vector<int>, greater<int> > pq;
		for(int i = 0; i < n; i++) {
			scanf("%d", &num);
			pq.push(num);
		}
		printf("%d", pq.top());
		for(int i = 1; i < n; i++) {
			pq.pop();
			printf(" %d", pq.top());
		}
		puts("");
		cin >> n;
	}
}