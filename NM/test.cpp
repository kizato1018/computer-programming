#include "matrix.h"
#include <iostream>

using namespace std;

int main() {
    Matrix A, b, x(6,1);
    A = NewMatrix();
    b = NewMatrix();
    cout << "A:" << endl;
    A.Show();
    cout << "b:" << endl;
    b.Show();
    x = Jacobi(A, b);
    cout << "x:" << endl;
    x.Show();

}

/*
6 6
3 -1 0 0 0 0.5
-1 3 -1 0 0.5 0
0 -1 3 -1 0 0
0 0 -1 3 -1 0
0 0.5 0 -1 3 -1
0.5 0 0 0 -1 3

6 1
2.5 1.5 1 1 1.5 2.5
*/