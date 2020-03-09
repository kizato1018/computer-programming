#include <bits/stdc++.h>
#define _min(a, b, c) min(min(a,b), min(a,c))
#define _for(i, a, b) for(int i = a; i < b; i++)


using namespace std;


int main() {
	int DP[1000][1000] = {0};
	int xn, yn;
	string x, y;
	while(cin >> xn >> x >> yn >> y){
		_for(i, 0, xn) {
			_for(j, 0, yn) {
				if(i > j)
					DP[i][j] = DP[i-1][j] +1;
				else if(j > i)
					DP[i][j] = DP[i][j-1] +1;
				else
					DP[i][j] = DP[i-1][j-1] +1;
				int d = abs(j-i);
				if(x[i] == y[j]) {
					DP[i][j] = _min(DP[i][d] + d-1,DP[i][j], (i>0 && j>0) ? DP[i-1][j-1] : 999);
					//DP[i][j] = abs(_min(DP[i][abs(j-i)] + (j-i), (j>0) ? DP[i][j-1] + 1 : 999, (i>0 && j>0) ? DP[i-1][j-1] : 999));
					if(i==0&&j==0)DP[i][j] = 0;
				}
				printf("%2d ", DP[i][j]);
			}
			cout << endl;
		}

//		cout << xn << ' ' << x << endl;
//		cout << yn << ' ' << y << endl;
	}

}

/*AGTAAGTAGGC
  A G T C T G A C G C
A 0 1 2 3 4 5 6 7 8 9
G 1 0 1 2 3 4 5 6 7 8
T 2 1 0 1 2 3 4 5 6 7
A 3 2 1 1 2 3 4 5 6 7
A 4 3 2 2 3 4 4 5 6 7 
G 5 4 3 3 3 3 4 5 6 7
T 6 5 4 4 4 3 3 4 5 6
A 7 6 5 4 4 4 4 5 6 7
G 8 7 6 5 5 5 5 5 6 6
G 9 8 7 6 6 6 
C  

  A G T C T G A C G C
A 0 
G 
T 
A 
A  
G 
T 
A 
G 
G  
C  

*/