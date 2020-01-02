#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "hw0604test.h"

void multiplication(uint8_t **result, uint8_t *size, uint8_t *x, uint8_t size_x, uint8_t *y, uint8_t size_y);

int main() {
	uint8_t size = size_x + size_y;
	uint8_t *result = calloc(size, sizeof(uint8_t));
	multiplication(&result, &size, x, size_x, y, size_y);
	if(*result) printf("%d", *result);
	for(uint8_t i = 1; i < size; i++)
		printf("%d", *(result + i));
	puts("");
}

void multiplication(uint8_t **result, uint8_t *size, uint8_t *x, uint8_t size_x, uint8_t *y, uint8_t size_y) {
	for(uint8_t i = size_x; i > 0; i--) {
		for(uint8_t j = size_y; j > 0; j--) {
			*(*result + i + j - 1) += *(x + i - 1) * *(y + j - 1);
		}
	}
	for(uint8_t i = *size; i > 1; i--) {
		//printf("r[%d] = %d\n", i - 1, *(*result + i - 1));
		*(*result + i - 2) += *(*result + i - 1) / 10;
		*(*result + i - 1) %= 10;
	}
}
