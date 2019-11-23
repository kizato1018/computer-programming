#include "inverse.h"

int32_t inverse(int32_t a, int32_t b, int32_t t0, int32_t t1){
	if(a % b == 0) return t1;
	return inverse(b, a % b, t1, t0 - a / b * t1);
}