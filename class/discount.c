#include <stdio.h>
#include <stdint.h>

void discount(int *price) {
	*price = (double)*price * 0.8;
}

int main(){
	int price = 0;
	printf("Please enter the price: ");
	scanf("%d", &price);
	discount(&price);
	printf("price with 20%% off = %d\n", price);
}