#include <iostream>
#include <cstdio>
#include <cmath>
#include "matrix.h"

const double PI = 3.1415926535897932384626433832795;

using namespace std;

double eq(int c, double x) {
    // Set equation (modify)
    switch(c) {
        case 0:
            return x;
            // return 1;
        case 1:
            return x;
            // return cos(2*PI*x);
        case 2:
            return x;
            // return sin(2*PI*x);
        case 3:
            return x;
            // return cos(4*PI*x);
        default:
            break;
    }
    return 0;
}

Matrix LSA(Matrix& t, Matrix& y, int n) {
    // Normal equations for least squares
    // Ax = b
    // ( (A^T)*A )x' = (A^T)*b


    Matrix A(t.Row(), t.Col()), ATA, b(y), c, r;
    double RMSE = 0;

    // Set A (modify)

    
    for(int i = 0; i < A.Row(); ++i) {
        for(int j = 0; j < A.Col(); ++j) {
            A[i][j] = eq(j, t[i][j]);
        }
    }

    // Set A done
    cout << "A:" << endl;
    A.Show();

    b = A.Transpose() * b;
    cout << "AT * b:" << endl;
    b.Show();
    ATA = A.Transpose() * A;
    cout << "ATA:" << endl;
    ATA.Show();
    c = Gaussian(ATA, b);
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
    // return c[0][0]*exp(c[1][0]*(x-1961));
    return c[0][0]*exp(c[1][0]*x);
}


Matrix LSA_exp(Matrix& t, Matrix& y, int n) {
    // ln(y) = 1*ln(c1) + c2*t
    //   b   =   *x1  +  x2

    Matrix A(t.Row(), 2), b(y), ATA, c, r(t.Row(), 1);
    double RMSE = 0;
    for(int i = 0; i < A.Row(); ++i) {
        A[i][0] = 1;
        A[i][1] = t[i][0];
        // b[i][0] = log(y[i][0]-279);
        b[i][0] = log(y[i][0]);
    }
    b = A.Transpose() * b;
    ATA = A.Transpose() * A;
    c = Gaussian(ATA, b);
    c[0][0] = exp(c[0][0]);
    // cout << "expf" << endl;
    for(int i = 0; i < A.Row(); ++i) {
        // cout << exp_f(c, t[i][0]) << endl;
        // r[i][0] = (y[i][0] - 279) - exp_f(c, t[i][0]);
        r[i][0] = y[i][0] - exp_f(c, t[i][0]);
    }
    for(int i = 0; i < r.Row(); ++i) {
        RMSE += r[i][0] * r[i][0];
    }
    RMSE = sqrt(RMSE/r.Row());
    cout << "RMSE=" << RMSE << endl;
    return c;
}


int main() {
    // Least Squares Approximation
    // Solving an inconsistent system
    // Find the “closest” x instead

    int N = 0, C = 0, mode = 0;
    cout << "How many equation: ";
    cin >> N;
    cout << "How many variable: ";
    cin >> C;

    cout << "1) Normal mode " << endl;
    cout << "2) Exponential mode " << endl;
    cin >> mode;
    

    Matrix t(N, C), y(N, 1), c(C, 1);
    // for(int i = 0; i < N; ++i) {
    //     t[i][0] = (double)i;
    // }
    t.Input();
    y.Input();


    switch (mode) {
    case 1:
        // LSA normal
        c = LSA(t, y, C);
        break;
    case 2:
        // LSA Exponential
        c = LSA_exp(t, y, C);
        break;
    default:
        break;
    }
    cout << "c:" << endl;
    c.Show();


}

/*
Example
Normal equation
x + y = 2
x - y = 1
x + y = 3

    [1  1]      [2]
A = [1 -1], b = [1]
    [1  1]      [3]

Input:
3 2
1
1 1
1 -1
1 1
2 1 3

*/

/*
2019 fin
Part 1 (c)
4
1
2
0 1 2 3
10 5 2 1
*/

/*
2019 fin
Part 2 #2
3
1
1
4 7 11
3 5 8
*/

/*
2018 fin
Part 1 (b)
4
1
2
-2 0 1 2
1 2 2 5
*/

/*
2017 fin
Part 1 (b)
5
3
1
3 -1 2
4 1 0
-3 2 1
1 1 5
-2 0 3
10 10 -5 15 0
*/