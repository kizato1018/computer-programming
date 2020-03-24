#include <iostream>
#include <cstdio>

using namespace std;

int main() {
	int n, d;
	cin >> n >> d;
	int a[n], b[n+1];
	bool flag = false;
	for(size_t i = 0; i < n; i++)
		cin >> a[i];
	b[0] = 0;
	for(size_t i = 1; i <= n; i++)
		b[i] = b[i-1] + a[n-i];
	for(size_t i = 1; i <= n; i++) {
		for(size_t j = 0; j < i; j++) {
			if(b[i] - b[j] == d) flag = true;
			else if(b[i] - b[j] < d) break;
		}
	}
	if(flag) cout << "yes" << endl;
	else cout << "no" << endl;
}
