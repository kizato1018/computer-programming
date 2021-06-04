#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

bool check(double a, double b) {
    return abs(a-b) < 0.000001;
}

double a(double x) {
    return pow(x,5)+x-3;
}

double b(double x) {
    return log(x)+2*x*x-3;
}

double c(double x) {
    return exp(x) + x - 7;
}

double Secant(double (*f)(double)) {
    double x = 1, temp = 2;
    while(!check(f(x), 0)) {
        x = x - (f(x) * (x-temp)) / (f(x) - f(temp));
    }
    return x;
}

int main() {
    printf("%.4lf\n", Secant(c));
}
