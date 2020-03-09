#include <bits/stdc++.h>

using namespace std;

int main() {
	int T = 1;
	bool m[25][25];
	bool visit[25];
	while(1){
		memset(m, 0, sizeof(m));
		int k;
		for(int i = 1; i <= 19; i++) {
			if(scanf("%d", &k) == EOF) return 0;
			for(int j = 0; j < k; j++) {
				int tmp;
				scanf("%d", &tmp);
				m[i][tmp] = true;
				m[tmp][i] = true;
			}
		}
		printf("Test Set #%d\n", T++);
		scanf("%d", &k);
		for(int i = 0; i < k; i++) {
			memset(visit, 0, sizeof(visit));
			int start, end, cnt = 0;
			scanf("%d %d", &start, &end);
			queue<int> q;
			q.push(start);
			q.push(0);
			while(q.front() != end) {
				visit[q.front()] = true;
				for(int j = 1; j <= 20; j++ ) {
					if(m[q.front()][j] && !visit[j])
						q.push(j);
				}
				q.pop();
				if(q.front() == 0) {
					cnt++;
					q.pop();
					q.push(0);
				}
			}
			printf("%2d to %2d: %d\n", start, end, cnt);
		}
		printf("\n");
	}

}