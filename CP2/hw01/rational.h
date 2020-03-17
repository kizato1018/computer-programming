#pragma once

struct rational {
	int p;
	int q;
};

int gcd(int a, int b);
int rational_set( struct rational *r, uint32_t p, uint32_t q)
int rational_print( const struct rational r);
void rational_add( struct rational *r, const struct rational r1, const struct
rational r2);
void rational_sub( struct rational *r, const struct rational r1, const struct
rational r2);
void rational_mul( struct rational *r, const struct rational r1, const struct
rational r2);
void rational_div( struct rational *r, const struct rational r1, const struct
rational r2);