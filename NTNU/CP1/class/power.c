#include <stdio.h>
#include <stdint.h>

uint64_t Power(int32_t x, int32_t y){
	if(y == 0)
		return 1;
	return Power(x, y - 1) * x;
}

int main(){
	int32_t base = 0;
	int32_t power = 0;
	uint64_t answer = 0;
	printf("Please enter the base number: ");
	scanf("%d", &base);
	printf("Please enter the power number: ");
	scanf("%d", &power);
	answer = Power(base, power);
	printf("answer: %lu\n", answer);
}