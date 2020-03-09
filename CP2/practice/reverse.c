#include <stdio.h>
#include <string.h>

int main() {
	char s[10000];
	while(fgets(s, sizeof(s), stdin)) {
		if(!strncmp("exit", s, strlen(s)-1))
			break;
		for (int i = strlen(s) - 2; i >= 0; i--) {
			fprintf(stdout, "%c", s[i]);
		}
		puts("");
	}
}