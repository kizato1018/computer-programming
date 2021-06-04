#include <bits/stdc++.h>

using namespace std;

int main() {
	while(1) {
		float a;
		float b;
		scanf("%f:%f", &a, &b);
		if(a == 0) break;
		a = 30 * a + 0.5 * b;
		b = 6 * b;
		printf("%.3f\n", min(abs(a - b), 360 - abs(a - b) ));

	}
}
