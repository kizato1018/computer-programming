#include <bits/stdc++.h>

using namespace std;

int main() {
	int coins[11] = {10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5};
	int64_t DP[30010] = {1, 0};
	for(int i = 0; i < 11; i++) {
		for(int j = coins[i]; j < 30001; j++)
			DP[j] += DP[j-coins[i]]; 
		}
	int a, b;
	while(scanf("%d.%d", &a, &b) != EOF && (a || b)) {
		printf("%3d.%02d%17lld\n", a, b, DP[a*100+b]);
	}

}