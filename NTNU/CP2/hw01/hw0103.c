#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool cmp(const char *str, const char *pt) {
	if((bool)*str ^ (bool)*pt) 
		if(*pt == '*') return cmp(str, pt+1);
	    else return false;
	if(*str == *pt) {
		if(!*str) return true;
		else return cmp(str+1, pt+1);
	}
	else if(*pt == '*') {
		if(*(pt+1) == '*') return cmp(str+1, pt+1);
		else if(*(pt+1) == '?') return cmp(str+1, pt+2) | cmp(str+1, pt);
		char *s = strchr(str, *(pt+1));
		if(s == NULL) return false;
		return cmp(s+1, pt+2) | cmp(s+1, pt);
	}
	else if(*pt == '?') return cmp(str+1, pt+1);
	else return false;
}

char* input() {
	size_t size = 2;
	char *s = calloc(2, sizeof(char));
	size_t i = 0;
	char buffer;
	while((buffer = getchar()) != '\n' && buffer != EOF) {
		if(i >= size-1) {
			size *= 2;
			s = realloc(s, sizeof(char) * size);
		}
		s[i++] = buffer;
	}
	s[i] = '\0';
	return s;
}

int main() {
	printf("Please enter the pattern: ");
	char *pattern = input();
	printf("Please enter the string: ");
	char *string = input();

	printf("Result:");
	char *voc = strtok(string, " ");
	while(voc != NULL) {
		if(cmp(voc, pattern))
			printf(" %s", voc);
		voc = strtok(NULL, " ");
	}
	puts("");
	free(pattern);
	free(string);
}