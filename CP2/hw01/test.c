#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main() {
	char *a = calloc(10, sizeof(char));
	a[0]=1;
	printf("%ld\n", strlen(a));
}