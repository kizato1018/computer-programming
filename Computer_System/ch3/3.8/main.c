#include <stdio.h>
#define N 5

int var_prod_ele_opt(long n, int A[n][n], int B[n][n], long i, long k);

int main() {
    int A[N][N], B[N][N];
    for(int i = 0; i < N*N; i++) {
        A[i/N][i%N] = i+1;
        B[i/N][i%N] = N-i;
    }
    printf("%d\n",var_prod_ele_opt(3, A, B, 0, 0));
}