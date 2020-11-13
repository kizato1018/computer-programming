#ifndef __MATRIX_H__
#define __MATRIX_H__
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

class Matrix {
public:
    Matrix() : row_(0), col_(0), v_(nullptr) {};
    Matrix(int, int);
    Matrix(const Matrix&);
    // Matrix(int r, int c, vector<vector<double> > val) : row_(r), col_(c), v(val) {};
    Matrix& operator=(const Matrix&);
    Matrix operator+(const Matrix&) const;
    Matrix operator*(const Matrix&) const;
    Matrix operator*(int) const;
    Matrix operator-(const Matrix&) const;
    const double* operator[] (int i) const { return v_[i]; } 
    double* operator[] (int i) { return const_cast<double*> (static_cast<const Matrix &>(*this)[i]); }
    bool operator==(const Matrix&) const;
    bool operator!=(const Matrix& M) const {return !(*this==M);}

    int Row() const {return row_;}
    int Col() const {return col_;}
    Matrix& Append(const Matrix&);
    Matrix Subtract(int);
    Matrix Inverse() const;

    Matrix& Input();
    void Show();

private:
    int row_;
    int col_;
    double **v_;

};
Matrix In(int);
Matrix NewMatrix ();
Matrix Elimination(Matrix, Matrix&, Matrix&, Matrix&, Matrix&);
Matrix Elimination(Matrix, Matrix&, Matrix&, Matrix&);
Matrix Gaussian(Matrix, Matrix);
Matrix Jacobi(Matrix A, Matrix b);
#endif