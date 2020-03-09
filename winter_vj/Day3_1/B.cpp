#include <bits/stdc++.h>

using namespace std;

struct item {
	int p, w;
}items[1010];

int main () {
	int T;
	scanf("%d", &T);
	while(T--) {
		int N;
		scanf("%d", &N);
		for(int i = 0; i < N; i++) 
			scanf("%d %d", &items[i].p, &items[i].w);

		int G;
		int carry;
		int sum = 0;
		scanf("%d", &G);
		for(int i = 0; i < G; i++){
			scanf("%d", &carry);
			int DP[35] = {0};
			for(int j = 0; j < N; j++) 
				for(int k = carry; k >= items[j].w; k--) 
					DP[k] = max(DP[k], DP[k-items[j].w] + items[j].p);
			sum += DP[carry];
		}
		printf("%d\n", sum);
	}
}