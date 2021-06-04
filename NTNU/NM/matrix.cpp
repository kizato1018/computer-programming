#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include "matrix.h"

using namespace std;


// class Matrix {
// public:
//     Matrix() : row_(0), col_(0), v_(nullptr) {};
//     Matrix(int, int);
//     Matrix(const Matrix&);
//     // Matrix(int r, int c, vector<vector<double> > val) : row_(r), col_(c), v(val) {};
//     Matrix& operator=(const Matrix&);
//     Matrix operator+(const Matrix&) const;
//     Matrix operator*(const Matrix&) const;
//     Matrix operator*(int) const;
//     Matrix operator-(const Matrix&) const;
//     const double* operator[] (int i) const { return v_[i]; } 
//     double* operator[] (int i) { return const_cast<double*> (static_cast<const Matrix &>(*this)[i]); }
//     bool operator==(const Matrix&) const;
//     bool operator!=(const Matrix& M) const {return !(*this==M);}

//     int Row() const {return row_;}
//     int Col() const {return col_;}
//     Matrix& Append(const Matrix&);
//     Matrix Subtract(int);

//     void Input();
//     void Show();

// private:
//     int row_;
//     int col_;
//     double **v_;

// };

Matrix::Matrix(int r, int c) : row_(r), col_(c) {
    v_ = new double*[row_];
    for(int i = 0; i < row_; ++i) {
        v_[i] = new double[col_];
        for(int j = 0; j < col_; ++j) {
            v_[i][j] = 0;
        }
    }
}

Matrix::Matrix(const Matrix& M) : row_(M.row_), col_(M.col_) {
    v_ = new double*[row_];
    for(int i = 0; i < row_; ++i) {
        v_[i] = new double[col_];
        for(int j = 0; j < col_; ++j)
            v_[i][j] = M[i][j];
    }
}

Matrix& Matrix::operator=(const Matrix& M) {
    for(int i = 0; i < row_; ++i) {
        delete [] v_[i];
    }
    delete [] v_;
    row_ = M.row_;
    col_ = M.col_;
    v_ = new double*[row_];
    for(int i = 0; i < row_; ++i) {
        v_[i] = new double[col_];
        for(int j = 0; j < col_; ++j)
            v_[i][j] = M[i][j];
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& M) const {
    Matrix tmp(*this);
    for(int i = 0; i < row_; ++i) {
        for(int j = 0; j < col_; ++j) {
            tmp[i][j] += M[i][j];
        }
    }
    return tmp;
}

Matrix Matrix::operator*(const Matrix& M) const {
    Matrix tmp(row_, M.col_);
    for(int i = 0; i < row_; ++i) {
        for(int j = 0; j < M.col_; ++j) {
            tmp[i][j] = 0;
            for(int k = 0; k < col_; ++k) {
                tmp[i][j] += (*this)[i][k] * M[k][j];
            }
            // printf("[%d][%d]=%lf\n", i, j, sum);
        }
    }
    return tmp;
}

Matrix Matrix::operator*(int c) const {
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
            if(abs((*this)[i][j] - M[i][j]) >= 0.00001)
                return false;
        }
    }
    return true;
}

Matrix& Matrix::Append(const Matrix& M) {
    int offset = col_;
    col_ += M.col_;
    for(int i = 0; i < row_; ++i) {
        double *tmp = new double[col_];
        for(int j = 0; j < offset; ++j) 
            tmp[j] = (*this)[i][j];
        for(int j = 0; j < M.Col(); ++j)
            tmp[j+offset] = M[i][j];
        delete [] v_[i];
        v_[i] = tmp;
    }
    return *this;
}

Matrix Matrix::Subtract(int c) {
    if(c < 0) c = col_ + c;
    int row = row_, col = col_ - c;
    Matrix tmp(row, col);
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            tmp[i][j] = (*this)[i][j+c];
        }
        v_[i] = (double*)realloc(v_[i], c * sizeof(double*));
    }
    return tmp;
}

Matrix Matrix::Inverse() const {
    Matrix tmp(*this);
    tmp.Append(In(row_));
    return tmp;
}

Matrix Matrix::Transpose() const {
    Matrix tmp(col_, row_);
    for(int i = 0; i < tmp.Row(); ++i) {
        for(int j = 0; j < tmp.Col(); ++j) {
            tmp[i][j] = (*this)[j][i];
        }
    }
    return tmp;
}

Matrix& Matrix::Input() {
    for(int i = 0; i < row_; ++i) {
        for(int j = 0; j < col_; ++j) {
            cin >> (*this)[i][j];
        }
    }
    return *this;
}

void Matrix::Show() const {
    for(int i = 0; i < row_; ++i) {
        for(int j = 0; j < col_; ++j) {
            printf("%.4lf ", (*this)[i][j]);
        }
        puts("");
    }
}

Matrix Matrix::Vector(int col) const {
    Matrix tmp(row_, 1);
    for(int i = 0; i < row_; ++i) {
        tmp[i][0] = (*this)[i][col];
    }
    return tmp;
}

double Matrix::length(int col) const {
    double l = 0;
    for(int i = 0; i < row_; ++i) {
        l += pow((*this)[i][col],2);
    }
    l = sqrt(l);
    return l;
}

Matrix In(int n) {
    Matrix In(n, n);
    for(int i = 0; i < n; ++i)
        In[i][i] = 1;
    return In;
}

Matrix D_Inv(Matrix& D) {
    Matrix D_inv(D);
    for(int i = 0; i < D.Row(); ++i) {
        D_inv[i][i] = 1 / D[i][i];
    }
    return D_inv;
}


Matrix Jacobi(Matrix A, Matrix b) {
    int r = A.Row(), c = A.Col();
    Matrix D(r, c), L(r, c), U(r, c), D_inv(r, c), pre_x(r, 1), x(r, 1);
    pre_x = x;
    for(int i = 0; i < r; ++i) {
        D[i][i] = A[i][i];
        for(int j = 0; j < i; ++j) {
            L[i][j] = A[i][j];
            U[j][i] = A[j][i];
        }
    }
    D_inv = D_Inv(D);
    cout << "D_inv:" << endl;
    D_inv.Show();
    cout << "L:" << endl;
    L.Show();
    cout << "U:" << endl;
    U.Show();
    cout << endl;

    int cnt = 0;
    do{
        printf("cnt=%d\n", ++cnt);
        cout << "prex: " << endl;
        pre_x.Show();
        pre_x = x;
        x = D_inv * (b - (L + U) * pre_x);
        cout << "x: " << endl;
        x.Show();
        if(cnt == 5) break;
    }while(x != pre_x);

    return x;
 }

Matrix NewMatrix () {
    int r, c;
    printf("enter (row col): ");
    cin >> r >> c;
    Matrix tmp(r, c);
    printf("enter matrix:\n");
    tmp.Input();
    return tmp;
}


Matrix Elimination(Matrix M, Matrix& L, Matrix& U, Matrix& P, Matrix& c) {
    int N = M.Row();
    P = In(N);
    L = In(N);
    for(int i = 0; i < N; ++i) {
        int max = i;
        for(int j = i+1; j < N; ++j) {
            if(abs(M[max][i]) < abs(M[j][i])) 
                max = j;
        }
        // Show(M);
        if(max != i) {
            for(int j = 0; j < N; ++j) {
                swap(P[max][j], P[i][j]);
                swap(M[max][j], M[i][j]);
            }
            swap(c[max][0], c[i][0]);
            // cout << "i: " << i << endl;
            // cout << "max: " << max << endl;
            // Show(M);
            // Show(P);
        }
        for(int j = i+1; j < N; ++j) {
            double d = M[j][i] / M[i][i];
            L[j][i] = d;
            for(int k = i; k < N; ++k) {
                M[j][k] -= M[i][k]*d; 
            }
            c[j][0] -= c[i][0]*d;
            // cout << "El:" << endl;
            // Matrix tmp(M);
            // tmp.Append(c).Show();
            // cout << endl;
        }
        if(max != i) {
            for(int j = 0; j < max && j < i; ++j) {
                swap(L[max][j], L[i][j]);
            }
        }
    }
    U = M;
    return M;
}

Matrix Elimination(Matrix M, Matrix& L, Matrix& U, Matrix& c) {
    Matrix P;
    return Elimination(M, L, U, P, c);
}

Matrix Elimination(Matrix M) {
    Matrix L, U, P, c;
    return Elimination(M, L, U, P, c);
}

Matrix Gaussian(Matrix M, Matrix c) {
    int N = M.Row();
    Matrix L, U, ans(N, 1);
    M = Elimination(M, L, U, c);
    M.Append(c);
    // Show(M);
    for(int i = N-1; i >= 0; --i) {
        for(int j = i; j < N; ++j) {
            M[i][N] -= (M[i][j] * ans[j][0]);
        }
        ans[i][0] = M[i][N] / M[i][i];
    }
    return ans;
}

bool equal(Matrix a, Matrix b) {
    for(int i = 0; i < a.Row(); ++i) {
        for(int j = 0; j < a.Col(); ++j) {
            if(abs(a[i][j]-b[i][j]) > 0.0001) return false;
        }
    }
    return true;
}
// int main() {
//     Matrix A, b, x;
//     A = NewMatrix();
//     b = NewMatrix();
//     cout << "A:" << endl;
//     A.Show();
//     cout << "b:" << endl;
//     b.Show();
//     // x = Jacobi(A, b);
//     cout << "A append B:" << endl;
//     A.Append(b);
//     A.Show();
//     x = A.Subtract(-1);
//     cout << "x:" << endl;
//     x.Show();

// }


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