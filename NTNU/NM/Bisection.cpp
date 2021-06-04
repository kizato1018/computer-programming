#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

bool check(double a) {
    return abs(a) < 0.00001;
}

double a(double x) {
    return exp(x-2) + pow(x,3) - x;
}

double Bisection(double a, double b, double (*f)(double)) {
    if(a > b) swap(a, b);
    double mid, k;
    do {
        mid = (a+b)/2;
        k = f(mid);
        if(k < 0) 
            a = mid;
        else
            b = mid;
    }while(!check(k));
    return mid;
}

int main() {
    printf("%.4lf\n", Bisection(-2, -1, a));
}