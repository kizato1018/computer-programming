#include <bits/stdc++.h>

using namespace std;
int k=0;
int disjoint_set[1000001] = {0};
void init(int num) {
	for(int i = 0; i < num; i++)
		disjoint_set[i] = i;
}

int Find(int x) {
	if(x == disjoint_set[x]) return x;
	else
		return disjoint_set[x] = Find(disjoint_set[x]);
}

void Union(int x, int y) {
	int a = Find(x);
	int b = Find(y);
	if(a != b){
		disjoint_set[a] = b;
		for(int i = 0; i < k; i++) printf("%d ", disjoint_set[i]);
		puts("");
}
}

int main() {
	int n;
	
	scanf("%d", &n);

	while(n-->0) {
		scanf("%d", &k);
		init(k);
		char choice;
		int a, b;
		int y = 0, no = 0;
		while(1) {
			scanf("%c", &choice);
			scanf("%c", &choice);
			if(choice == '\n')
				break;
			scanf("%d %d", &a, &b);
			switch(choice) {
				case 'c':
					Union(a, b);
					break;
				case 'q':
					if(Find(a) == Find(b)) y++;
					else no++;
					break;
				default:
					break;
			}
		}

		cout << y << "," << no << endl;
		cout << endl;
	}
}
