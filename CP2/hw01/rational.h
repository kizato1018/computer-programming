#pragma once

struct rational {
	int32_t p;
	int32_t q;
};

int gcd(int32_t a, int32_t b);
int rational_set( struct rational *r, int32_t p, int32_t q);
int rational_print( const struct rational r);
void rational_add( struct rational *r, const struct rational r1, const struct rational r2);
void rational_sub( struct rational *r, const struct rational r1, const struct rational r2);
void rational_mul( struct rational *r, const struct rational r1, const struct rational r2);
void rational_div( struct rational *r, const struct rational r1, const struct rational r2);