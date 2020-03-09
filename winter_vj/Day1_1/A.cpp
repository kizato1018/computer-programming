#include <bits/stdc++.h>

using namespace std;

struct data{
	char c;
	int cnt;
};

bool cmp(data a, data b){
	if(a.cnt == b.cnt)
		return a.c < b.c;
	else
		return a.cnt > b.cnt;
}

int main()
{
	int n;
	char buffer;
	while(cin >> n) {
		data d[26] = {0};
		buffer = getchar();
		for(int i = 0; i < 26; i++) d[i].c = 'A' + i;
		while(n > 0) {
			string s;
			getline(cin, s);
			for(int i = 0; i < s.length(); i++) {
				if('a' <= s[i] && s[i] <= 'z') d[s[i]-'a'].cnt++;
				else if('A' <= s[i] && s[i] <= 'Z') d[s[i]-'A'].cnt++;
			}
			n--;
		}
		sort(d, d + 26, cmp);
		for(int i = 0; i < 26; i++){
				if(d[i].cnt)
					cout << d[i].c << " " << d[i].cnt << endl;
		}
	}
	return 0;
}