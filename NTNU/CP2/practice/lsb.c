#include <stdio.h>
#include <stdint.h>

int main() {
	FILE *fin = NULL;
	FILE *fout = NULL;
	char message[256] = {};
	uint8_t f = 1;
	if((fin = fopen("maldives.bmp", "rb")) == NULL) {
		printf("read error\n");
		return(1);
	}
	if((fout = fopen("maldives_m.bmp", "wb")) == NULL) {
		printf("creat error\n");
		return(1);
	}

}
