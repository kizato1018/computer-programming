// #include "matrix.h"
#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
#include <cstdlib>

using namespace std;

class Matrix {
public:
    Matrix() : row_(0), col_(0) {};
    Matrix(const Matrix& M) : row_(M.row_), col_(M.col_), v(M.v) {};
    Matrix(int r, int c, vector<vector<double> > val) : row_(r), col_(c), v(val) {};
    Matrix& operator=(const Matrix&);
    Matrix operator+(const Matrix&) const;
    Matrix operator*(const Matrix&) const;
    Matrix operator*(const int) const;
    Matrix operator-(const Matrix&) const;
    const vector<double> operator[] (int i) const { vector<double> r = v[i]; return r; } 
    vector<double>& operator[] (int i) {return v[i];}
    bool operator==(const Matrix&) const;

    bool operator!=(const Matrix& M) const {return !(*this==M);}

    int Row() {return row_;}
    int Col() {return col_;}

    void Input();
    void Show();

    vector<vector<double> > v;
private:
    int row_;
    int col_;

};

Matrix& Matrix::operator=(const Matrix& M) {
    row_ = M.row_;
    col_ = M.col_;
    v = M.v;
    return *this;
}

Matrix Matrix::operator+(const Matrix& M) const {
    Matrix tmp(*this);
    for(int i = 0; i < row_; ++i) {
        for(int j = 0; j < col_; ++j) {
            tmp[i][j] += M.v[i][j];
        }
    }
    return tmp;
}

Matrix Matrix::operator*(const Matrix& M) const {
    vector<vector<double> > tmp;
    for(int i = 0; i < row_; ++i) {
        vector<double> tmpv;
        for(int j = 0; j < M.col_; ++j) {
            double sum = 0;
            for(int k = 0; k < col_; ++k) {
                sum += v[i][k] * M.v[k][j];
            }
            // printf("[%d][%d]=%lf\n", i, j, sum);
            tmpv.push_back(sum);
        }
        tmp.push_back(tmpv);
    }
    Matrix result(row_, M.col_, tmp);
    return result;
}

Matrix Matrix::operator*(const int c) const {
    Matrix tmp(*this);
    for(int i = 0; i < row_; ++i) {
        for(int j = 0; j < col_; ++j) {
            tmp[i][j] *= c;
        }
    }
    return tmp;
}

Matrix Matrix::operator-(const Matrix& M) const{
    Matrix tmp(*this), M1(M);
    // tmp = tmp + M1;
    tmp = tmp + (M * -1);
    return tmp;
}

bool Matrix::operator==(const Matrix& M) const {
    for(int i = 0; i < row_; ++i) {
        for(int j = 0; j < col_; ++j) {
            if(abs(v[i][j] - M[i][j]) >= 0.00001)
                return false;
        }
    }
    return true;
}

void Matrix::Input() {
    printf("enter (row col): ");
    cin >> row_ >> col_;
    printf("enter matrix:\n");
    for(int i = 0; i < row_; ++i) {
        vector<double> tmp;
        for(int j = 0; j < col_; ++j) {
            double d;
            cin >> d;
            tmp.push_back(d);
        }
        v.push_back(tmp);
    }
}

void Matrix::Show() {
    for(int i = 0; i < row_; ++i) {
        for(int j = 0; j < col_; ++j) {
            printf("%.4lf ", v[i][j]);
        }
        puts("");
    }
}

Matrix D_Inv(Matrix& D) {
    Matrix D_inv;
    D_inv = D;
    for(int i = 0; i < D.Row(); ++i) {
        D_inv[i][i] = 1 / D[i][i];
    }
    return D_inv;
}


 void Jacobi(Matrix A, Matrix b, Matrix& x) {
    Matrix D, L, U, D_inv, pre_x;
    D = A;
    L = A;
    U = A;
    x = b;
    for(int i = 0; i < x.Row(); ++i) x[i][0] = 0;
    pre_x = x;
    for(int i = 0; i < A.Row(); ++i) {
        if(i >= 1) {
            D[i-1][i] = 0;
            D[i][i-1] = 0;
            L[i-1][i] = 0;
            U[i][i-1] = 0;
        }
        L[i][i] = 0;
        U[i][i] = 0;
    }
    D_inv = D_Inv(D);
    // cout << "D_inv:" << endl;
    // D_inv.Show();

    int cnt = 0;
    do{
        // printf("cnt=%d\n", ++cnt);
        // cout << "prex: " << endl;
        // pre_x.Show();
        pre_x = x;
        x = D_inv * (b - (L + U) * pre_x);
        // cout << "x: " << endl;
        // x.Show();
    }while(x != pre_x);

    return;
 }


int main() {
    Matrix A, b, x;
    A.Input();
    b.Input();
    cout << "A:" << endl;
    A.Show();
    cout << "b:" << endl;
    b.Show();
    Jacobi(A, b, x);
    cout << "x:" << endl;
    x.Show();

}


/*
10 10
3 -1 0 0 0 0 0 0 0 0
-1 3 -1 0 0 0 0 0 0 0
0 -1 3 -1 0 0 0 0 0 0 
0 0 -1 3 -1 0 0 0 0 0
0 0 0 -1 3 -1 0 0 0 0
0 0 0 0 -1 3 -1 0 0 0
0 0 0 0 0 -1 3 -1 0 0
0 0 0 0 0 0 -1 3 -1 0
0 0 0 0 0 0 0 -1 3 -1
0 0 0 0 0 0 0 0 -1 3 
10 1
2 1 1 1 1 1 1 1 1 2

2 2
3 1
1 2
2 1
5 5

*/