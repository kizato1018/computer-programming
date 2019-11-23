#include <stdio.h>
#include "inverse.h"

int main(){
	int32_t m, n, inv;
	printf("Please enter the moduale: ");
	scanf("%d", &m);
	printf("Please enter the number: ");
	scanf("%d", &n);
	inv = inverse(m, n, 0, 1);
	while(inv < 0) inv += m;
	printf("The modular multiplicative inverse of %d is %d.\n", n, inv);
}