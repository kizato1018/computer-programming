#include <bits/stdc++.h>

using namespace std;

int main() {
	int N, M;
	int DP[101][101] = {{1}};
	for(int i = 0; i < 101; i++) {
		for(int j = 0; j < 101; j++) {
			if(j == 0 || i == j) DP[i][j] = 1;
			else DP[i][j] = DP[i-1][j] + DP[i-1][j-1];
		}
	}
	while(scanf("%d %d", &N, &M) != EOF && (N || M)) {		
		printf("%d things taken %d at a time is %d exactly.\n", N, M, DP[N][M]);
	}
}
