#include <stdio.h>
#include <stdint.h>

int32_t gcd(int32_t a, int32_t b) {
	if(b == 0) return a;
	return gcd(b, a % b);
}

int32_t lcm(int32_t a, int32_t b) {
	return a * b / gcd(a, b);
}

int main() {
	int32_t n, tmp;
	printf("Please enter the variable number: ");
	scanf("%d", &n);
	int32_t equat[n][n+1];
	for(int32_t i = 1; i <= n; i++) {
		if(i % 10 == 1 && i != 11)
			printf("Please enter the %dst equation\n");
		else if(i % 10 == 2 && i != 12)
			printf("Please enter the %dnd equation\n");
		else if(i % 10 == 3 && i != 13)
			printf("Please enter the %drd equation\n");
		else
			printf("Please enter the %dth equation\n");
		for(int32_t j = 1; j <= n + 1; j++) {
			scanf("%d", &equat[i-1][j-1]);
		}
	}
	for(int32_t i = 0; i < n - 1; i++) {
		for(int32_t j = i; j < n - 1; j++) {
			tmp = lcm(equat[i][i], equat[j+1][i]);
			for(int32_t k = 0; k < n + 1; k++) {
				equat[j][k] *= tmp;
				equat[j+1][k] = equat[j+1][k] * tmp - equat[j][k];
			}
		}
	}
}
