#include <iostream>
#include <cstdio>
#include <vector>
#define MAX 1e6

using namespace std;

int main() {
	int N;
	vector<int> dp = vector<int> (MAX+10, 0);
	dp[0] = 1;
	for(int i = 1; i <= MAX; i++)
		if(i & 1)
			dp[i] = dp[i-1];
		else
			dp[i] = (dp[i-1] + dp[i/2]) % 1000000000;	
	while(scanf("%d", &N) != EOF) {
		printf("%d\n", dp[N]);
	}
}