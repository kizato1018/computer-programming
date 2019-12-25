#include <stdio.h>
#include <stdint.h>

int main() {
	int32_t n;
	printf("Please enter the variable number: ");
	scanf("%d", &n);
	int32_t equat[n][n+1];
	for(int32_t i = 1; i <= n; i++) {
		if(i % 10 == 1 && i != 11)
			printf("Please enter the %dst equation: ", i);
		else if(i % 10 == 2 && i != 12)
			printf("Please enter the %dnd equation: ", i);
		else if(i% 10 == 3 && i != 13)
			printf("Please enter the %drd equation: ", i);
		else 
			printf("Please enter the %dth equation: ", i);
		for(int32_t j = 1; j <= n + 1; j++)
			scanf("%d", &equat[i-1][j-1]);
	}
	for(int32_t i = 0; i < n; i++)
		for(int32_t j = 0; j < n; j++)
			if(i != j)
				for(int32_t k = n; k >= 0; k--)
					equat[j][k] = equat[j][k] * equat[i][i] - equat[i][k] * equat[j][i];
	printf("Answer:\n");
	for(int32_t i = 0; i < n; i++)
		printf("x%d = %d\n", i + 1, equat[i][n] / equat[i][i]);
}