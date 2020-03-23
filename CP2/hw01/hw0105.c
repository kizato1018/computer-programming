#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "rational.h"
#define MAX 2

char* input() {
	size_t size = MAX;
	char *s = calloc(MAX, sizeof(char));
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
	struct rational *r;
	uint8_t *operator;
	printf("Please enter the equation: ");
	char *eq = input();
	r = calloc(strlen(eq), sizeof(struct rational));
	operator = calloc(strlen(eq), sizeof(char));

	char *token = strtok(eq, "(), ");
	while(token != NULL) {
		while(*token == ' ') token++;
		switch(*token) {
			case '+':
				*operator = 1;
			case '-':
				*operator = 2;
			case '*':
				*operator = 3;
			case '/':
				*operator = 4;
		}
	}
}

/*
an = x * 

*/