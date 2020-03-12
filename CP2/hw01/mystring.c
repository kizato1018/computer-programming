#include <stdio.h>
#include <stdint.h>

char *mystrchr(const char *s, int c) {
	size_t i = 0;
	while(*(s+i))
		if(*(s+i) == c) return (char *)(s+i);
		else i++;
	return NULL;
}
char *mystrrchr(const char *s, int c) {
	size_t i = 0;
	while(*(s+i)) i++;
	while(i)
		if(*(s+i) == c) return (char *)(s+i);
		else i--;
	return NULL;
}
size_t mystrspn(const char *s, const char *accept) {
	uint8_t T[256] = {0};
	size_t i = 0;
	while(*(accept+i)) {
		T[*(accept+i)] = 1;
		i++;
	}
	i = 0;
	while(*(s+i)) {
		if(!T[*(s+i)]) break;
		i++;
	}
	return i;
}
size_t mystrcspn(const char *s, const char *reject) {
	uint8_t T[256] = {0};
	size_t i = 0;
	while(*(reject+i)) {
		T[*(reject+i)] = 1;
		i++;
	}
	i = 0;
	while(*(s+i)) {
		if(T[*(s+i)]) break;
		i++;
	}
	return i;
}
char *mystrpbrk(const char *s, const char *accept) {
	return (*(s+mystrcspn(s, accept))) ? (char *)(s+mystrcspn(s, accept)) : NULL;
}
char *mystrstr(const char *haystack , const char *needle) {
	size_t cnt= 0;
	for(size_t i = 0; *(haystack+i); i++) {
		if(*(haystack+i) == *(needle+cnt)) cnt++;
		else cnt = 0;
		if(!*(needle+cnt)) return (char *)(haystack+i-cnt+1);
	}
}
char *mystrtok(char *str, const char *delim) {
	static char *s;
	if(str) s = str;
	else s++;
	while(*(s))
		if(*(s) == *delim) return s;
		else s++;
	return NULL;
}
