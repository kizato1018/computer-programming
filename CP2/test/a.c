#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #define GREEN \033[0;32;32m
// #define RESET \033[m
int main() {
	char a[] = "for(int i = 0; i < 10; i++)";
	char *token = strtok(a, " ();");
	while(token != NULL) {
		printf("%s", token);
		token = strtok(NULL, " ();");
	}
}