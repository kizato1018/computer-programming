#include <stdio.h>
#include <stdint.h>
#include <math.h>

int main(){
	int32_t d = 0, x = 0, y = 0;
	printf("Please enter the degree: ");
	scanf("%d", &d);
	printf("Please enter the coefficients: ");
	int32_t c[d];
	for(int32_t i = 0; i < d + 1; i++) {
		scanf("%d", &c[i]);
	}
	printf("Please enter x: ");
	scanf("%d", &x);
	for(int32_t i = 0; i <= d; i++) {
		for(int32_t j = 0; j <= d - i; j--) {
			y += c[d-j] * pow(x, j);
			c[d-j] *= j;
		}
		if(i > 0) {
			printf("f^%d(%d) = %d\n", i, x, y);
		}
		else
			printf("f(%d) = %d\n", x, y);
	}
}
