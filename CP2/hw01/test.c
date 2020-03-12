#include <stdio.h>
#include <string.h>

int main () {
	const char *a = "ABCDEF";
	//char b[] = "ABCD";
	//printf("%ld\n", strspn(a,b));
	for(int i = 0; i < 6; i++) printf("%c",*(a+i));
}
