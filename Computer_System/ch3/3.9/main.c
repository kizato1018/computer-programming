#include <stdio.h>

int F1(long n, int A[n][n], int B[n][n], long i, long k);




int main() {
    int A[3][3], B[3][3];
    for(int i = 0; i < 9; ++i) {
        A[i/3][i%3] = i+1;
        B[i/3][i%3] = 9-i;
    }
    printf("%d\n", F1(3, A, B, 0, 2));
}