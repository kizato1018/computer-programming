#include "matrix.h"
#include <iostream>
#include <cmath>

using namespace std;

Matrix GetD(const Matrix v) {
    double x = v[0][0];
    double y = v[1][0];
    double z = v[2][0];
    Matrix tmp(3,3);
    tmp[0][0] = 1;
    tmp[0][1] = 1;
    tmp[0][2] = 1;
    tmp[1][0] = 2*x;
    tmp[1][1] = 2*y;
    tmp[1][2] = 2*z;
    tmp[2][0] = exp(x)+y-z;
    tmp[2][1] = x;
    tmp[2][2] = -1 * x;
    return tmp;
}
Matrix GetF(const Matrix v) {
    double x = v[0][0];
    double y = v[1][0];
    double z = v[2][0];
    Matrix tmp(3, 1);
    tmp[0][0] = x+y+z-3;
    tmp[1][0] = x*x+y*y+z*z-5;
    tmp[2][0] = exp(x)+x*y-x*z-1;
    return tmp * -1;
}

void Multi_Newton() {
    int cnt = 20;
    Matrix x(3, 1), prev(x), s(3, 1), D(3, 3), F(3,1);
    prev = x.Input();
    while(--cnt) {
        D = GetD(x);
        // D.Show();
        F = GetF(x);
        // F.Show();
        s = Gaussian(D, F);
        cout << "s:" << endl;
        s.Show();
        cout << endl;
        x = prev + s;
        cout << "x:" << endl;
        x.Show();
        prev = x;
        cout << endl;
    }
    x.Show();

}

int main() {
    Multi_Newton();
}