#ifndef __MATRIX_H__
#define __MATRIX_H__
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

class Matrix {
public:
    Matrix() : row_(0), col_(0), v_(nullptr) {};
    Matrix(int row, int col);
    Matrix(const Matrix&);
    // Matrix(int r, int c, vector<vector<double> > val) : row_(r), col_(c), v(val) {};
    Matrix& operator=(const Matrix&);
    Matrix operator+(const Matrix&) const;
    Matrix operator*(const Matrix&) const;
    Matrix operator*(int) const;
    friend Matrix operator*(int c, const Matrix& m) {return m*c;}
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
    Matrix Transpose() const;
    Matrix Vector(int col) const;
    double length(int col) const;

    Matrix& Input();
    void Show() const;

private:
    int row_;
    int col_;
    double **v_;

};
Matrix In(int); // 單元矩陣
Matrix NewMatrix (); // 忘記了
Matrix Elimination(Matrix M, Matrix& L, Matrix& U, Matrix& P, Matrix& c); // 消去
Matrix Elimination(Matrix M, Matrix& L, Matrix& U, Matrix& c); // 消去
Matrix Gaussian(Matrix A, Matrix b);
Matrix Jacobi(Matrix A, Matrix b);
bool equal(Matrix a, Matrix b);
#endif