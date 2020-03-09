#include <bits/stdc++.h>

using namespace std;

int main() {
	int N;
	while(scanf("%d", &N) != EOF) {
		int M[105][105] = {0};
		int Max = -99999999;
		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= N; j++) {
				scanf("%d", &M[i][j]);
				M[i][j] += M[i][j-1];
			}
		}

		for(int i = 0; i < N; i++) {
			for(int j = i+1; j <= N; j++){
				int sum = 0;
				for(int k = 1; k <= N; k++) {
					int now = M[k][j] - M[k][i];
					sum = max(now, now + sum);
					Max = max(Max, sum);
				}
			}
		}
		printf("%d\n", Max);
	}
}
