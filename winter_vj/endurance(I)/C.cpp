#include <bits/stdc++.h>

using namespace std;

int main() {
	int c = 1;
	while(1) {
		int n;
		cin >> n;
		if(!n) break; 
		int a[n];
		int avg = 0;
		int cnt = 0;
		for(int i = 0; i < n; i++) {
			cin >> a[i];
			avg += a[i];
		}
		avg /= n;
		for(int i = 0; i < n; i++)
			if(a[i] > avg) cnt += a[i] - avg;
		printf("Set #%d\nThe minimum number of moves is %d.\n", c++, cnt);
		puts("");
	}
}