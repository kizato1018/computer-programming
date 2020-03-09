#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	while(n--) {
		int a[4];
		for(int i = 0; i < 4; i++)
			cin >> a[i];
		sort(a, a+4);
		if(a[0] + a[1] + a[2] <= a[3])
			cout << "banana" << endl;
		else{
			if(a[0] == a[1] && a[2] == a[3]){
				if(a[1] == a[2])
					cout << "square" << endl;
				else
					cout << "rectangle" << endl;
			}
			else
				cout << "quadrangle" << endl;
		}
	}
}
