#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	while(n--) {
		int digit[10] = {0};
		int a;
		cin >> a;
		for(int i = 1; i <= a; i++) {
			int num = i;
			while(num){
				digit[num%10]++;
				num /= 10;
			}
		}
		printf("%d", digit[0]);
		for(int i = 1; i < 10; i++)
			printf(" %d",digit[i]);
		puts("");
	}
}
