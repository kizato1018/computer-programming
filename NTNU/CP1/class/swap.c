#include <stdio.h>
#include <stdint.h>

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main(){
	int a, b;
	printf("Please enter 2 number: ");
	scanf("%d %d", &a, &b);
	swap(&a, &b);
	printf("After swap: %d %d\n",a ,b);
}