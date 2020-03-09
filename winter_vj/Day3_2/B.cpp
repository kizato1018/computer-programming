#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	while(n--) {
		int num;
		bool noans = true;
		scanf("%d", &num);
		for(int i = 54; i > 0 ; i--) {
			int test = num - i;
			int tmp = test;
			while(tmp){
				test += tmp % 10;
				tmp /= 10;
			}
			if(num == test) {
				printf("%d\n", num - i);
				noans = false;
				break;
			}
		}
		if(noans) printf("0\n");
	}
}