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
    // x_0 = inital vector
    //    x_{k+1} = x_k - ( D(x_k)^T * D(x_k) )^-1 * D(x_k)^T * r(x_k) 
    // => v_k = -( D(x_k)^T * D(x_k) )^-1 * D(x_k)^T * r(x_k)
    // => ( D(x_k)^T * D(x_k) ) * v_k = -( D(x_k)^T * r(x_k) ) 

    int k = a.Row();
    Matrix x(a.Col(), 1);
    Matrix D(k, a.Col()), r(k, 1);
    Matrix v(a.Col(), 1);
    // r.Show();
    for(int cnt = 0; cnt < 1000; ++cnt) {
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
    // Gauss Newton
    // 
    int N = 0;
    cout << "How many points: ";
    cin >> N;
    Matrix a(N, 2), R(N, 1);
    a.Input();
    R.Input();
    Gauss_Newton(a, R).Show();
}

/*
3
-1 0
1 1
1 -1
1 1 1
*/

/*
2019 fin
Part 1 (e)
3
2 1
5 3
5 -3
1 2 1
*/

/*
2019 fin
Part 2 #3

r = x+y+z-10
    x/y-y/z
    xy-6
    yz-6

Dr =   1          1      1
     1/y -x/y^2-1/z  y/z^2
       y          x      0
       0          z      y
*/

/*
2018 fin
Part 1 (d)
4
2 1
5 3
5 -3
8 -10
1 2 1 4
*/

/*
2017 fin
Part 1 (d)
3
-1 0
1 1
1 -1
1 1 1

*/