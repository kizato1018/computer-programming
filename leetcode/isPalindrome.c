#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool isPalindrome(int64_t x) {
	if(x < 0) return false;
	int64_t result = 0;
	int64_t var = x;
	while(var) {
		result *= 10;
		result += var % 10;
		var /= 10;
	}
	if(result == x)
		return true;
	else 
		return false;
}

int main() {
	int64_t x;
	scanf("%ld", &x);
	printf("%d\n", isPalindrome(x));
}