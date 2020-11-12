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
<<<<<<< HEAD
            tmp[i][j] += M.v[i][j];
=======
            tmp[i][j] += M[i][j];
>>>>>>> 7e89d1f003aaafcad3734b62cd8e5e536fe78bb0
        }
    }
    return tmp;
}

Matrix Matrix::operator*(const Matrix& M) const {
<<<<<<< HEAD
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
=======
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
>>>>>>> 7e89d1f003aaafcad3734b62cd8e5e536fe78bb0
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
<<<<<<< HEAD
            if(abs(v[i][j] - M[i][j]) >= 0.00001)
=======
            if(abs((*this)[i][j] - M[i][j]) >= 0.00001)
>>>>>>> 7e89d1f003aaafcad3734b62cd8e5e536fe78bb0
                return false;
        }
    }
    return true;
}

<<<<<<< HEAD
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
=======
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

void Matrix::Input() {
    for(int i = 0; i < row_; ++i) {
        for(int j = 0; j < col_; ++j) {
            cin >> (*this)[i][j];
        }
>>>>>>> 7e89d1f003aaafcad3734b62cd8e5e536fe78bb0
    }
}

void Matrix::Show() {
    for(int i = 0; i < row_; ++i) {
        for(int j = 0; j < col_; ++j) {
<<<<<<< HEAD
            printf("%.4lf ", v[i][j]);
=======
            printf("%.4lf ", (*this)[i][j]);
>>>>>>> 7e89d1f003aaafcad3734b62cd8e5e536fe78bb0
        }
        puts("");
    }
}

<<<<<<< HEAD
Matrix D_Inv(Matrix& D) {
    Matrix D_inv;
    D_inv = D;
=======
Matrix In(int n) {
    Matrix In(n, n);
    for(int i = 0; i < n; ++i)
        In[i][i] = 1;
    return In;
}

Matrix D_Inv(Matrix& D) {
    Matrix D_inv(D);
>>>>>>> 7e89d1f003aaafcad3734b62cd8e5e536fe78bb0
    for(int i = 0; i < D.Row(); ++i) {
        D_inv[i][i] = 1 / D[i][i];
    }
    return D_inv;
}


<<<<<<< HEAD
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

=======
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


Matrix Elimination(Matrix M, Matrix& L, Matrix& U, Matrix& P) {
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

Matrix Elimination(Matrix M, Matrix& L, Matrix& U) {
    Matrix P;
    return Elimination(M, L, U, P);
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

>>>>>>> 7e89d1f003aaafcad3734b62cd8e5e536fe78bb0

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