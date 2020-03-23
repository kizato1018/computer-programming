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

bool cmp(char a, char b) {
	int x, y;
	switch (a) {
		case '+': case '-': 
			x = 1;
			break;
		case '*': case '/': 
			x = 2;
			break;
	}
	switch (b) {
		case '+': case '-': 
			y = 1;
			break;
		case '*': case '/': 
			y = 2;
			break;
	}
	return x <= y;
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
	//memset(operator, 0, strlen(eq) * sizeof(char));

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
				rational_set(&r[i++], a, b);
				break;
			default:
				break;
		}
		token = strtok(NULL, "(), ");
	}
	for(int i = 0; i<5; i++) {
		rational_print(r[i]);
	}
	for(int i = 0, j = 0; i < strlen(operator); i++, j++) {
		operator[j] = operator[i];
		switch(operator[i]) {
			case '*':
				rational_mul(&r[operator[j-1]], r[operator[j-1]], r[operator[i+1]]);
				operator[j] = 0; i++; j--;
				break;
			case '/':
				rational_div(&r[operator[j-1]], r[operator[j-1]], r[operator[i+1]]);
				operator[j] = 0; i++; j--;
				break;
			default:
				break;
		}	 
	}
	for(int i = 0; i<5; i++) {
		rational_print(r[i]);
	}
	for(int i = 0, j = 0; i < strlen(operator); i++, j++) {
		operator[j] = operator[i];
		switch(operator[i]) {
			case '+':
				rational_add(&r[operator[j-1]], r[operator[j-1]], r[operator[i+1]]);
				operator[j] = 0; i++; j--;
				break;
			case '-':
				rational_sub(&r[operator[j-1]], r[operator[j-1]], r[operator[i+1]]);
				operator[j] = 0; i++; j--;
				break;
			default:
				break;
		}	 
	}
	rational_print(*r);
}

/*
an = x * 
1+2*3/4+5*6
1+2+5
*/