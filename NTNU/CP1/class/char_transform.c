#include <stdio.h>
#include <stdint.h>

int main() {
	char c;
	while(scanf("%c", &c) != EOF) {
		if(c >= 'a' && c <= 'z') c = c - 'A' + 'a';
		else if(c >= 'A' && c <= 'Z') c = c - 'a' + 'A';
		printf("%c\n", c);
	}
}