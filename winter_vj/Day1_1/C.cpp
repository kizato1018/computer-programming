#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	while(cin >> n) {
		int num[n];
		int cnt = 0;
		for(int i = 0; i < n; i++) cin >> num[i];
		for(int i = 0; i < n; i++)
			for(int j = 1; j < n - i; j++)
				if(num[j-1] > num[j]) {
					swap(num[j-1], num[j]);
					cnt++;
				}
		cout << "Minimum exchange operations : " << cnt << endl;
	}
}