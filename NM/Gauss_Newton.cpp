#include <iostream>
#include <cmath>
#include "matrix.h"

using namespace std;


Matrix GetD(const Matrix x, const Matrix a) {
    Matrix tmp(a.Row(),a.Col());
    for(int i = 0; i < a.Row(); ++i) {
        for(int j = 0; j < a.Col(); ++j) {
            tmp[i][j] = (x[j][0] - a[i][j]) / sqrt(pow(x[0][0] - a[i][0], 2) + pow(x[1][0] - a[i][1], 2));
            // tmp[i][j] = 0.5 * pow(pow(x[0][0] - a[i][0], 2)+pow(x[1][0] - a[i][1], 2), -0.5) * 2*(x[j][0] - a[i][j]);
        }
    }
    return tmp; 
}

Matrix Gauss_Newton(const Matrix a, const Matrix R) {
    int k = a.Row();
    Matrix x(a.Col(), 1);
    Matrix D(k, a.Col()), r(k, 1);
    Matrix v(a.Col(), 1);
    // r.Show();
    for(int cnt = 0; cnt < 4; ++cnt) {
        for(int i = 0; i < k; ++i) {
            r[i][0] = sqrt(pow(x[0][0] - a[i][0], 2) + pow(x[1][0] - a[i][1], 2)) - R[i][0];
        }
        D = GetD(x, a);
        v = Gaussian(D.Transpose() * D, -1 * D.Transpose() * r);
        // cout << "cnt=" << cnt << endl;
        // cout << "x:" << endl;
        // x.Show();
        // cout << "D:" << endl;
        // D.Show();
        // cout << "r:" << endl;
        // r.Show();
        // cout << "DT * D:" << endl;
        // (D.Transpose() * D).Show();
        // cout << "-DT * r:" << endl;
        // (-1 * D.Transpose() * r).Show();
        // cout << "V:" << endl;
        // v.Show();
        
        x = x + v;
        // cout << "new x:" << endl;
        // x.Show();
        // cout << endl;
    }
    return x;
}
int main() {
    Matrix a(3, 2), R(3, 1);
    a.Input();
    R.Input();
    Gauss_Newton(a, R).Show();
}

/*
-1 0
1 1
1 -1
1 1 1
*/