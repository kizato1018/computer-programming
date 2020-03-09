#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	while(n--) {
		int a;
		int num;
		cin >> a;
		vector<int> v;
		for(int i = 0; i < a; i++) {
			cin >> num;
			v.push_back(num);
		}
		cout << (*max_element(v.begin(), v.end()) - *min_element(v.begin(), v.end())) * 2 << endl;

	}
}
