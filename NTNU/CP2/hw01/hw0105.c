#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "rational.h"

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

void push(char *st, char op) {
	st[strlen(st)] = op;
}

int main() {
	struct rational *r;
	char *operator;
	int32_t a, b;
	int32_t i = 0;
	printf("Please enter the equation: ");
	char *eq = input();
	r = calloc(strlen(eq), sizeof(struct rational));
	operator = calloc(strlen(eq), sizeof(char));

	char *token = strtok(eq, "(), ");
	while(token != NULL) {
		switch(*token) {
			case '+': case '-': case '*': case '/':
				push(operator, *token);
				break;
			case '0' ... '9':
				a = atoi(token);
				token = strtok(NULL, "(), ");
				b = atoi(token);
				push(operator, i);
				if(rational_set(&r[i++], a, b) == -1) {
					printf("Wrong input\n");
					return 0;
				}
				break;
			default:
				printf("Wrong input\n");
				return 0;
		}
		token = strtok(NULL, "(), ");
	}
	for(int i = 0, j = 0; i < strlen(operator); i++, j++) {
		operator[j] = operator[i];
		switch(operator[i]) {
			case '*':
				rational_mul(&r[operator[j-1]], r[operator[j-1]], r[operator[i+1]]);
				i++; j--;
				break;
			case '/':
				rational_div(&r[operator[j-1]], r[operator[j-1]], r[operator[i+1]]);
				i++; j--;
				break;
			default:
				break;
		}	 
	}
	for(int i = 0, j = 0; i < strlen(operator); i++, j++) {
		
		operator[j] = operator[i];
		switch(operator[i]) {
			case '+':
				rational_add(&r[operator[j-1]], r[operator[j-1]], r[operator[i+1]]);
				i++; j--;
				break;
			case '-':
				rational_sub(&r[operator[j-1]], r[operator[j-1]], r[operator[i+1]]);
				i++; j--;
				break;
			default:
				break;
		}	 
	}
	rational_print(*r);
}

