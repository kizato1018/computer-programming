#include <iostream>
#include <vector>

#define _for(i,a,b) for(int i = a; i < b; i++)

using namespace std;

struct Matrix {
    Matrix(int c, int r);
    void Get();
    void Print();
    Matrix operator+(Matrix tar);
    void operator=(Matrix tar);

    vector<vector<int>> value;
    int col;
    int row;
};

Matrix::Matrix(int c, int r) {
    col = c, row = r;
    _for(i, 0, r) {
        vector<int> v;
        _for(j, 0, c) {
            v.push_back(0);
        }
        value.push_back(v);
    }
}

void Matrix::Print() {
    _for(i, 0, row) {
        _for(j, 0, col) {
            cout << value[i][j] << " ";
        }
        cout << endl;
    }
}

void Matrix::Get() {
    _for(i, 0, row) {
        _for(j, 0, col) {
            cin >> value[i][j];
        }
    }
}


Matrix Matrix::operator+(Matrix tar) {
    Matrix tmp(2,2);
    _for(i, 0, row)
        _for(j, 0, col)
           tmp.value[i][j] = value[i][j] + tar.value[i][j];
    return tmp;
}

void Matrix::operator=(Matrix tar) {
    _for(i, 0, row)
        _for(j, 0, col)
           value[i][j] = tar.value[i][j];
}

int main() {
    Matrix a(2,2), b(2,2), c(2,2);
    cout << "input a:" << endl;
    a.Get();
    cout << "----------" << endl;
    a.Print();
    cout << "input b:" << endl;
    b.Get();
    cout << "----------" << endl;
    b.Print();
    cout << "----------" << endl;
    c = a + b;
    c.Print();
    cout << "----------" << endl;
}