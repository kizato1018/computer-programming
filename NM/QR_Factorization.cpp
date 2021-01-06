#include <iostream>
#include <cmath>
#include "matrix.h"

using namespace std;

void QR(Matrix& A, Matrix& Q, Matrix& R) {
    int dim = A.Row();
    Q = A;
    for(int i = 0; i < A.Col(); ++i) {
        Matrix a = A.Vector(i);
        for(int j = 0; j < i; ++j) {
            double d = (Q.Vector(j).Transpose()*A.Vector(i))[0][0];
            a = a - Q.Vector(j) * d;
            R[j][i] = d;
        }
        for(int k = 0; k < dim; ++k) {
            Q[k][i] = (double)a[k][0] / a.length(0);
        }
        R[i][i] = a.length(0);
    }
}

int main() {
    int Row = 0, Col = 0;
    cout << "Row: ";
    cin >> Row;
    cout << "Column: ";
    cin >> Col;
    Matrix A(Row,Col), Q(A), R(Col, Col);
    A.Input();
    A.Show();
    QR(A, Q, R);
    cout << "Q:" << endl;
    Q.Show();
    cout << "R:" << endl;
    R.Show();

}

/*
3 3
4 8 1
0 2 -2
3 6 7
*/

/*
2019 fin
Part 1 (d)
4 3
1 -2 -1
2 0 1
2 -4 2
4 0 0
*/