#include <iostream>
#include <cstdio>

using namespace std;
int M[10010][10010] = {0};
int main() {
    int N, K;
    
    scanf("%d %d", &N, &K);
    for(int i = 1; i <= N/K; ++i) {
        int tmp = 0;
        for(int j = 0; j < K; ++j) {
            scanf("%d", &tmp);
            M[i][i] += tmp;
        }
    }
    int a,b,c,j, B,A;
    for(int k = 1; k < N/K; ++k) {
        for(int i = 1; i <= N/K - k; ++i) {
            j = i + k;
            a = M[j-1][i+1];
            b = M[j][i+2];
            c = M[j-2][i];
            M[j][i] = max(M[i][i] + min(M[j-1][i+1], M[j][i+2]), M[j][j] + min(M[j-1][i+1], M[j-2][i]));
            // printf("(%d,%d):%d %d %d\n",i,j,a,b,c);
        }
    }
    // printf("\n");
    // for(int i = 1; i <= N/K; i++) {
    //     for(int j = 1; j <= i; j++) {
    //         printf("%2d ", M[i][j]);
    //     }
    //     printf("\n");
    // }
    B = M[N/K][1];
    A = min(M[N/K][2], M[N/K-1][1]);
    if(B>A)
        printf("Bogay\n");
    else if(A>B)
        printf("aserf18766\n");
    else
        printf("TIE\n");
    printf("%d %d", B, A);
    
}
// 1+12+16
