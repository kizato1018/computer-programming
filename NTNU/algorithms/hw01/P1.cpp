#include <iostream>
#include <cstdio>
#define MOD 1000000007
using namespace std;

struct Matrix{
    int64_t v[2][2] = {{1,0},{0,1}};
};

Matrix M_mul(const Matrix a, const Matrix b) {
    Matrix r;
    for(size_t i = 0; i < 2; i++) {
        for(size_t j = 0; j < 2; j++) {
            r.v[i][j] = 0;
            for(size_t k = 0; k < 2; k++) {
                r.v[i][j] += (a.v[i][k] * b.v[k][j]) % MOD;
            }
            r.v[i][j] %= MOD;
        }
    }
    return r;
}

Matrix pwn(const Matrix M, int n) {
    Matrix r, base = M;
    while(n) {
        if(n&1) r = M_mul(r, base);
        base = M_mul(base, base);
        n >>= 1;
    }
    return r;
}

int main () {
    Matrix M;
    Matrix A;
    Matrix I;
    int n;
    cin >> A.v[1][0] >> A.v[0][0] >> M.v[0][0] >> M.v[0][1] >> n;
    M.v[1][0] = 1; M.v[1][1] = 0;
    A.v[0][1] = 0; A.v[1][1] = 0;
    cout << M_mul(pwn(M, n-2), A).v[0][0] << endl;
}