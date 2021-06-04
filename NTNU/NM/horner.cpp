#include <stdio.h>

double P(double x) {
    double result = 1;
    int i = 0;
    for(i = 0; i < 50; ++i) {
        result = result * x + 1;
    }
    return result;
}

int main() {
	double input = 0;
	printf("Please input your number: ");
	scanf("%lf", &input);
    printf("%lf\n", P(input));
}
