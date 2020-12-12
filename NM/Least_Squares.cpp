#include <iostream>
#include <cstdio>
#include <cmath>
#include "matrix.h"

const double PI = 3.141592;

using namespace std;

double eq(int c, double x) {
    switch(c) {
        case 0:
            return 1;
        case 1:
            return cos(2*PI*x);
        case 2:
            return sin(2*PI*x);
        case 3:
            return cos(4*PI*x);
        default:
            break;
    }
    return 0;
}

Matrix LSA(Matrix& t, Matrix& y, int n) {
    Matrix A(t.Row(), n), M, b(y), c, r;
    double RMSE = 0;
    for(int i = 0; i < A.Row(); ++i) {
        for(int j = 0; j < n; ++j) {
            A[i][j] = eq(j, t[i][0]);
        }
    }
    // M.Show();
    // t.Show();
    b = A.Transpose() * b;
    cout << "AT * b:" << endl;
    b.Show();
    M = A.Transpose() * A;
    c = Gaussian(M, b);
    cout << "A*c" << endl;
    (A*c).Show();
    r = (A * c) - y;
    cout << "r:" << endl;
    r.Show();
    for(int i = 0; i < r.Row(); ++i) {
        RMSE += r[i][0] * r[i][0];
    }
    RMSE = sqrt(RMSE/r.Row());
    cout << "RMSE=" << RMSE << endl;

    return c;
}

double exp_f(Matrix& c, double x) {
    return c[0][0]*exp(c[1][0]*(x-1961));
}


Matrix LSA_exp(Matrix& t, Matrix& y, int n) {
    Matrix A(t.Row(), 2), b(y), M, c, r(t.Row(), 1);
    double RMSE = 0;
    for(int i = 0; i < A.Row(); ++i) {
        A[i][0] = 1;
        A[i][1] = i;
        b[i][0] = log(y[i][0]-279);
    }
    b = A.Transpose() * b;
    M = A.Transpose() * A;
    c = Gaussian(M, b);
    c[0][0] = exp(c[0][0]);
    // cout << "expf" << endl;
    for(int i = 0; i < A.Row(); ++i) {
        // cout << exp_f(c, t[i][0]) << endl;
        r[i][0] = exp_f(c, t[i][0]) - (y[i][0] - 279);
    }
    for(int i = 0; i < r.Row(); ++i) {
        RMSE += r[i][0] * r[i][0];
    }
    RMSE = sqrt(RMSE/r.Row());
    cout << "RMSE=" << RMSE << endl;
    return c;
}


int main() {
    // LSA

    Matrix t(12, 1), y(12, 1), c(4, 1);
    for(int i = 0; i < 12; ++i) {
        t[i][0] = (double)i/12;
    }
    y.Input();
    c = LSA(t, y, 4);
    cout << "c:" << endl;
    c.Show();

    // LSA_exp

    // Matrix t(50,1), y(50, 1), c(2, 1);
    // for(int i = 0; i < 50; ++i)
    //     t[i][0] = 1961+i;
    // y.Input();
    // c = LSA_exp(t, y, 2);
}