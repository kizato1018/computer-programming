#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct T {
	uint8_t a;
	uint32_t c;
	uint16_t b;
};

int main () {
//	printf("%ld\n", sizeof(struct T));

	char str[] = "(10,2)  + (5, -678)*(3,10)";
	char s[] = "(), ";
	size_t i = 0;

	char *token = strtok(str, s);
	while(token != NULL) {
		printf("%s\n", token);
		token = strtok(NULL, s);
	}
/*
	char c = 'a';
	switch(c) {
		case '0' ... '9':
			printf("%c\n", c);
	}
*/
	return 0;
}
