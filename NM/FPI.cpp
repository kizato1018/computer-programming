#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

bool check(double a, double b) {return abs(a-b) < 0.0001;}

double f(double x) {
    while(!check(x*6+5, sin(x))) {
        x = (sin(x)-5)/6;
    }
    return x;
}

double g(double x) {
    while(!check(x*x*x, 2*x+2)) {
        x = pow((2*x+2), 1.0/3);
    }
    return x;
}

double a(double x) {
    while(!check(x*x*x, x - exp(x-2))) {
        x = pow((x-exp(x-2)), 1.0/3);
    }
    return x;
}

int main() {
    double x = 3;
    printf("%.4lf\n", a());
}
