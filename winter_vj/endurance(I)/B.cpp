#include <bits/stdc++.h>

using namespace std;

int main() {
	int c = 1;
	int a;
	int cnt;

	while(1) {
		int tmp = 0;
		cnt = 0;
		cin >> a;
		if(a < 0) break;
		else {
			while(a > 1){
				tmp = a % 2;
				a = a / 2 + tmp;
				cnt++;
			}
			printf("Case %d: %d\n",c++, cnt);
		}
	}
}
