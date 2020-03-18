#include <iostream>

using namespace std;

int main() {
	int t;
	cin >> t;
	while(t--) {
		string s;
		int d;
		cin >> s >> d;
		if(((s[9] - '0') % 2) ^ (d % 2))
			cout << "No" << endl;
		else 
			cout << "Yes" << endl;
	}
}