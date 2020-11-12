#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include "matrix.h"

using namespace std;

int N;
vector<vector<double> > P;
vector<vector<double> > M;
vector<vector<double> > L, U;
vector<double> ans;

void init_P() {
    for(int i = 0; i < N; ++i) {
        vector<double> tmp;
        for(int j = 0; j < N; ++j) {
            tmp.push_back(i == j);
        }
        P.push_back(tmp);
    }
}

void init_L() {
    for(int i = 0; i < N; ++i) {
        vector<double> tmp;
        for(int j = 0; j < N; ++j) {
            tmp.push_back(i == j);
        }
        L.push_back(tmp);
    }
}

void Show(vector<vector<double> > m) {
    cout << "---------------" << endl;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
    cout << "----------------" << endl;
}

void elimination() {
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
    }
    U = M;
}

void Gaussian() {
    elimination();
    // Show(M);
    for(int i = N-1; i >= 0; --i) {
        for(int j = i; j < N; ++j) {
            M[i][N] -= (M[i][j] * ans[j]);
        }
        ans[i] = M[i][N] / M[i][i];
    }
}

void LU() {
    init_P();
    init_L();
    // for(int i = 0; i < N; ++i) {
    //     L[i][N] = M[i][N];
    // }
    elimination();
    Show(P);
    // Show(L);
    // for(int i = 0; i < N; ++i) {
    //     for(int j = i+1; j < N; ++j) {
    //         L[j][N] -= L[i][N] * L[j][i];
    //         cout << L[j][N] << " ";
    //     }
    //     cout << endl;
    //     U[i][N] = L[i][N];
    // }
    // // Show(U);
    // for(int i = N-1; i >= 0; --i) {
    //     for(int j = i; j < N; ++j) {
    //         U[i][N] -= (U[i][j] * ans[j]);
    //     }
    //     ans[i] = U[i][N] / U[i][i];
    // }

}

int main() {
    cin >> N;
    for(int i = 0; i < N; ++i) {
        vector<double> tmp;
        double input;
        for(int j = 0; j < N; ++j) {
            cin >> input;
            tmp.push_back(input);
        }
        M.push_back(tmp);
        ans.push_back(0);
    }
    LU();
    // for(auto i : ans) {
    //     cout << i << " ";
    // }
    cout << endl;
}

/*
3
1 2 -1 3
2 1 -2 3
-3 1 1 -6

4
2 1 0 0 1
0 1 2 0 1
2 4 5 1 2
8 5 0 3 0

3
2 1 5
4 4 -4
1 3 1

4
4.0 2.0 -1.0 3.0
3.0 -4.0 2.0 5.0
-2.0 6.0 -5.0 -2.0
5.0 1.0 6.0 -3.0

*/