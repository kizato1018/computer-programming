#include <iostream>
#include <cstdio>

using namespace std;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, d;
	cin >> n >> d;
	int a[n], c = 0;
	bool flag = false;
	for(size_t i = 0; i < n; i++) {
		cin >> a[i];
		if(flag) continue;
		for(int j = c; j < i; j++) {
			a[j] += a[i];
			if(a[j] > d) c++;
			else if(a[j] == d) flag = true;
		}
	}
	if(flag) cout << "yes" << endl;
	else cout << "no" << endl;
}
