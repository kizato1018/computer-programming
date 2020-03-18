#include <stdio.h>

int gcd(int a, int b) {
	if(b == 0) return a;
	return gcd(b, a%b);
}

int rational_set(struct rational *r, uint32_t p, uint32_t q) {
	if(q==0) return -1;
	int d = gcd(p, q);
	r->p /= d;
	r->q /= d;
}

int rational_print(const struct rational r) { printf("(%d,%d)", r.p, r.q); }

void rational_add(struct rational *r, const struct rational r1, const struct rational r2) {
	if(rationral_set(r, r1.p * r2.q + r2.p * r1.q, r1.q * r2.q))
		return r; 
}

void rational_sub(struct rational *r, const struct rational r1, const struct rational r2) {
	if(rationral_set(r, r1.p * r2.q - r2.p * r1.q, r1.q * r2.q))
		return r; 
}

void rational_mul(struct rational *r, const struct rational r1, const struct rational r2) {
	if(rationral_set(r, r1.p * r2.p, r1.q * r2.q))
		return r; 
}

void rational_div(struct rational *r, const struct rational r1, const struct rational r2) {
	if(rationral_set(r, r1.p * r2.q, r1.q * r2.p))
		return r; 
}