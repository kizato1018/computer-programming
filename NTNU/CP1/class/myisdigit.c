#include <stdio.h>
#include <stdint.h>

int myisdigit(int c) {
	return (c >= '0' && c <= '9');
}

int main() {
	for(uint8_t i = 0; i < 128; i++) {
		if(myisdigit(i))
			printf("%c is a digit.\n", i);
		else
			printf("%c is not a digit.\n", i);
	}
}