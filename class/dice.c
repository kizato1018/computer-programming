#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int32_t a[6] = {0};
	srand(time(NULL));
	for(int32_t i = 0; i < 60000; i++)
		a[rand() % 6]++;
	for(size_t i = 0; i < 6; i++)
		printf("%ld: %d\n",i, a[i]);
}