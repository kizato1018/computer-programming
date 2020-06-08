#include <stdio.h>
#include <string.h>

int main() {
	FILE *fp = fopen("test.txt", "r");
	char context[10000] = {};
	while(!feof(fp)) {
		fgets(context, sizeof(context), fp);
		char *a = strtok(context, "\"");
		char *b, *c;
		b = strtok(NULL, "\"");
		c = strtok(NULL, "\"");
		printf(" %s %s %s\n", a, b, c);
	}

}