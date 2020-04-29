#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

struct rational {
    int32_t a;
    int32_t b;
    int32_t c;
};

int gcd(int32_t a, int32_t b) {
	if(b == 0) return a;
	return gcd(b, a%b);
}

void rational_print(const struct rational r) { printf("(%d,%d,%d)", r.a, r.b, r.c); }

int rational_set(struct rational *r, int32_t a, int32_t b, int32_t c) {
	if(c==0) return -1;
    int8_t sign = 1;
    if(a < 0) {sign *= -1; a *= -1;}
    if(b < 0) {sign *= -1; b *= -1;}
    if(c < 0) {sign *= -1; c *= -1;}
    int32_t d = gcd(b, c);
	// r->b = b / d;
	// r->c = c / d;
    r->a = (a + b / c) * sign;
    r->b = (b % c) / d ;// * (r->a == 0) ? sign : 1;
    r->c = c / d;
    if(r->a == 0)
        r->b *= sign; 
    // printf("%d %d %d, ", a, b, c);
    // rational_print(*r);
	return 0;
}



void rational_add(struct rational *r, const struct rational r1, const struct rational r2) {
    // rational_print(r1);
    // printf("+");
    // rational_print(r2);
    // printf("\n");
    rational_set(r, 0, (r1.b + r1.a * r1.c) * r2.c + (r2.b + r2.a * r2.c) * r1.c, r1.c * r2.c);
}

void rational_sub(struct rational *r, const struct rational r1, const struct rational r2) {
    // rational_print(r1);
    // printf("-");
    // rational_print(r2);
    // printf("\n");
	rational_set(r, 0, (r1.b + r1.a * r1.c) * r2.c - (r2.b + r2.a * r2.c) * r1.c, r1.c * r2.c);
}

void rational_mul(struct rational *r, const struct rational r1, const struct rational r2) {
    // rational_print(r1);
    // printf("*");
    // rational_print(r2);
    // printf("\n");
	rational_set(r, 0, (r1.b + r1.a * r1.c) * (r2.b + r2.a * r2.c), r1.c * r2.c);
}

void rational_div(struct rational *r, const struct rational r1, const struct rational r2) {
    // rational_print(r1);
    // printf("/");
    // rational_print(r2);
    // printf("\n");
	rational_set(r, 0, (r1.b + r1.a * r1.c) * r2.c, r1.c * (r2.b + r2.a * r2.c));
}

void push(char *st, char op) {
	st[strlen(st)] = op;
}

int main() {
	struct rational r[2000];
	char operator[2000];
	int32_t a, b, c;
	int32_t i = 0;
	printf("Please enter the equation: ");
	char eq[10000];
    fgets(eq, sizeof(eq), stdin);
    if(eq[strlen(eq)-1] == '\n')
        eq[strlen(eq)-1] = 0;

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
                token = strtok(NULL, "(), ");
                c = atoi(token);
				push(operator, i);
				if(rational_set(&r[i++], a, b, c) == -1) {
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

