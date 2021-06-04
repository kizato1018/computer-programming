#include <stdio.h>
#include <stdint.h>

int main() {
    int32_t a;
	uint32_t k = 0x80000000;
	scanf("%d", &a);
	while(k) {
		printf("%d", (a & k) ? 1 : 0);
		k >>= 1;
	}
	puts("");
}