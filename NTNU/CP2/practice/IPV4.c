#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char s[100];
	int ip;
	char *token;
	fgets(s, sizeof(s), stdin);
	s[strlen(s)-1]=0;
	token = strtok(s, ".");

	while(token) {
		ip = atoi(token);
		if(ip > 255 || ip < 0) {
			printf("invalid\n");
			return 0;
		}
		else
			printf("%d",ip);
		token = strtok(NULL, ".");
		
	}
}