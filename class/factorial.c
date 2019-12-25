#include <stdio.h>
#include <stdint.h>

uint64_t factorial(int32_t i){
	if(i == 2)
		return 2;
	return factorial(i - 1) * i;
}

int main(){
	int32_t number = 0;
	uint64_t answer = 0;

	printf("Please enter an interger: ");
	scanf("%d", &number);
	answer = factorial(number);
	printf("Answer: %lu\n", answer);

}