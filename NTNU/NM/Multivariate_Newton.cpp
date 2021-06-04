#include "matrix.h"
#include <iostream>
#include <cmath>

using namespace std;

Matrix GetD(const Matrix v, int eq, int N) {
    //          [ df1/dx df1/dy df1/dz ]
    //  D(v) =  [ df2/dx df2/dy df2/dz ]
    //          [ df3/dx df3/dy df3/dz ]

    double x = v[0][0];
    double y = v[1][0];
    double z = v[2][0];
    Matrix tmp(eq ,N);
    tmp[0][0] = (double)1;
    tmp[0][1] = (double)1;
    tmp[0][2] = (double)1;
    tmp[1][0] = (double)2*x;
    tmp[1][1] = (double)2*y;
    tmp[1][2] = (double)2*z;
    tmp[2][0] = (double)exp(x)+y-z;
    tmp[2][1] = (double)x;
    tmp[2][2] = (double)-1 * x;
    return tmp;
}
Matrix GetF(const Matrix v, int eq) {
    // F(v) = F(f1, f2, f3)

    double x = v[0][0];
    double y = v[1][0];
    double z = v[2][0];
    // double k = v[0][0];
    Matrix tmp(eq, 1);
    tmp[0][0] = (double)x+y+z-3;
    tmp[1][0] = (double)x*x+y*y+z*z-5;
    tmp[2][0] = (double)exp(x)+x*y-x*z-1;
    return tmp * -1;
}

void Multi_Newton(int eq, int N) {
    // D(v) * s = -F(v)

    Matrix v(N, 1), prev(v), s(N, 1), D(eq, N), F(eq, 1);
    // initial vector
    prev = v.Input();
    for(int i = 0; i < 20; ++i) {
        D = GetD(v, eq, N);
        cout << "D:" << endl;
        D.Show();
        F = GetF(v, eq);
        cout << "F:" << endl;
        F.Show();    
        s = Gaussian(D, F);
        cout << "s:" << endl;
        s.Show();
        cout << endl;
        v = prev + s;
        cout << "x:" << endl;
        v.Show();
        prev = v;
        cout << endl;
    }
    v.Show();

}

int main() {
    // Solving nonlinear systems
    // Multivariate Newton
    int eq = 0, N = 0;
    cout << "How many equation: ";
    cin >> eq;
    cout << "How many variable: ";
    cin >> N;
    Multi_Newton(eq, N);
}

/*

*/