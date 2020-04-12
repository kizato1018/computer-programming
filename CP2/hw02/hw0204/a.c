#include <stdio.h>
#include "test.h"
int main(){
	printf("Running 14 test cases:\n");
         	printf("1) fibonacci(-5): %s\n",(-5 == fibonacci(-5)) ? "PASS" : "WRONG");
	printf("2) fibonacci(-1): %s\n",(-1 == fibonacci(-1)) ? "PASS" : "WRONG");
	printf("3) fibonacci(0): %s\n",(0 == fibonacci(0)) ? "PASS" : "WRONG");
	printf("4) fibonacci(1): %s\n",(1 == fibonacci(1)) ? "PASS" : "WRONG");
	printf("5) fibonacci(2): %s\n",(1 == fibonacci(2)) ? "PASS" : "WRONG");
	printf("6) fibonacci(3): %s\n",(2 == fibonacci(3)) ? "PASS" : "WRONG");
	printf("7) fibonacci(10): %s\n",(55 == fibonacci(10)) ? "PASS" : "WRONG");
	printf("8) factorial(-5): %s\n",(1 == factorial(-5)) ? "PASS" : "WRONG");
	printf("9) factorial(-1): %s\n",(1 == factorial(-1)) ? "PASS" : "WRONG");
	printf("10) factorial(0): %s\n",(1 == factorial(0)) ? "PASS" : "WRONG");
	printf("11) factorial(1): %s\n",(1 == factorial(1)) ? "PASS" : "WRONG");
	printf("12) factorial(2): %s\n",(2 == factorial(2)) ? "PASS" : "WRONG");
	printf("13) factorial(3): %s\n",(6 == factorial(3)) ? "PASS" : "WRONG");
	printf("14) factorial(8): %s\n",(40320 == factorial(8)) ? "PASS" : "WRONG");
	return 0;
}
