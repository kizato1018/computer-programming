#include <bits/stdc++.h>

using namespace std;

int main() {
	int n, m;
	while(scanf("%d %d", &n, &m) != EOF && (n || m)) {
		int num;
		bool cards[2][100010] = {false};
		vector<int> v1, v2;
		for(int i = 0; i < n; i++) {
			scanf("%d", &num);
			v1.push_back(num);
			cards[0][num] = true;
		}
		for(int i = 0; i < m; i++) {
			scanf("%d", &num);
			v2.push_back(num);
			cards[1][num] = true;
		}
		int cnt = 0;
		for(int i = 0; i < v1.size(); i++) {
			if(!cards[1][v1[i]]){
				//printf("v1[%d] = %d", i, v1[i]);
				for(int j = 0; j < v2.size(); j++) {
					//printf("v2[%d] = %d", i, v2[i]);
					if(!cards[0][v2[j]]) {
						//printf("|%d %d|\n", v1[i], v2[j]);
						v1.push_back(v2[j]);
						v2.push_back(v1[i]);
						cards[0][v2[j]] = true;
						cards[1][v1[i]] = true;
						cnt++;
						break;
					}
				}
			}
		}
		printf("%d\n", cnt);
	}
}