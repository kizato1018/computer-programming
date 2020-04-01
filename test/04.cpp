#include <iostream>
#include <vector>


using namespace std;

int main() {
	vector<string> v;
	v.push_back("abcde");
	v.push_back("012345");
	v.push_back("HaHaha");

	for(int i = 0; i < 3; i++) {
		cout << v[i][3] << endl;
	}
	return 0;
}