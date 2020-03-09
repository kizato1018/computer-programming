#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	while(n--) {
		int a = 0;
		for(int i = 0; i < 4; i++) {
			int input;
			cin >> input;
			for(int j = 0; j < 4; j++) {
				int tmp = (input % 10);
				if(j % 2) tmp *= 2;
				if(tmp > 9) tmp = tmp % 10 + tmp / 10;
				a += tmp;
				input /= 10;
			}
		}
		if(a % 10) printf("Invalid\n");
		else printf("Valid\n");
	}
}
