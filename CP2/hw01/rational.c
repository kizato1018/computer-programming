#include <stdio.h>
#include <stdint.h>
#include "rational.h"

int gcd(int32_t a, int32_t b) {
	if(b == 0) return a;
	return gcd(b, a%b);
}

int rational_set(struct rational *r, int32_t p, int32_t q) {
	if(q==0) return -1;
	int32_t d = gcd(p, q);
	r->p = p / d;
	r->q = q / d;
	return 0;
}

int rational_print(const struct rational r) { printf("(%d,%d)", r.p, r.q); }

void rational_add(struct rational *r, const struct rational r1, const struct rational r2) {
	rational_set(r, r1.p * r2.q + r2.p * r1.q, r1.q * r2.q);
}

void rational_sub(struct rational *r, const struct rational r1, const struct rational r2) {
	rational_set(r, r1.p * r2.q - r2.p * r1.q, r1.q * r2.q);
}

void rational_mul(struct rational *r, const struct rational r1, const struct rational r2) {
	rational_set(r, r1.p * r2.p, r1.q * r2.q);
}

void rational_div(struct rational *r, const struct rational r1, const struct rational r2) {
	rational_set(r, r1.p * r2.q, r1.q * r2.p);
}