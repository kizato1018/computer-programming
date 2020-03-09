#include <bits/stdc++.h>

using namespace std;

int main() {
	int N;
	int m;
	while(cin >> N >> m) {
		int cnt = 1;
		int n = N;
		while(1){
			if(n < 1 || m < 1) {
				printf("Boring!\n");
				break;
			}
			if(n == 1) {
				if(cnt == 1) {
					printf("Boring!\n");
					break;
				}
				printf("%d", N);
				for(int i = 1; i < cnt; i++){
					N /= m;
					printf(" %d", N);
				}
				puts("");
				break;
			}
			if(n % m || m == 1) {
				printf("Boring!\n");
				break;
			}
			n /= m;
			cnt++;
		}
	}
}
