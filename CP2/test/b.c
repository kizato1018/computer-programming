#include <stdio.h>
#include <stdint.h>

int main() {
	int16_t a=1060;
	FILE *pF = NULL;
	pF = fopen("Binarytest", "wb");
	fwrite(&a, 2, 1, pF);
	fclose(pF);
}
