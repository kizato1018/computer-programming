#include "test.h"

int fibonacci(int n)
{
if (n <= 1)
return n;
return fibonacci(n - 1) + fibonacci(n - 2);
}

int factorial(int n) {
int result = 1;
for (int i = 1; i <= n; i++) {
result *= i;
}
return result;
}