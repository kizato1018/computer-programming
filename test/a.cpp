#include <bits/stdc++.h>
#define _for(i,a,b) for(int i = a; i < b; i++)

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const vector<T> &v) {
	for(auto &p : v) os << p << " ";
		return os;
}

int get_data() {int x; cin >> x; return x;}

int main() {
	vector<int> v;
	_for(i, 0, 10) v.push_back(i);
	cout << v << endl;
	_for(i,0,10) {
		if(i<5) continue;
		cout << i << " ";
	} 
}