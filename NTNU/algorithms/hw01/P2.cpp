#include <iostream>
#include <cstdio>

using namespace std;

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int64_t n, d;
	cin >> n >> d;
	int64_t a[n], b = 0, c = 0;
	bool flag = false;
	for(size_t i = 0; i < n; i++) {
		cin >> a[i];
		if(flag) break;
		b += a[i];
		while(b > d) b -= a[c++];
		if(b == d) flag = true;
	}
	if(flag) cout << "yes" << endl;
	else cout << "no" << endl;
}
