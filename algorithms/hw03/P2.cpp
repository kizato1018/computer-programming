#include <iostream>
#include <cstdio>

using namespace std;

int a[10010] = {0};
int dp[10010][10010] = {0};
int df[10010][10010] = {0};

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    for(int i = 0; i < N; ++i) {
        scanf("%d", &a[i]);
        for(int j = 0; j < i; ++j) {
            df[i][j] = abs(a[i] - a[j]);
            df[j][i] = dp[i][j];
        }
    }
    for(int i = 1; i < N; ++i) {
        for(int j = 0; j+i < N; ++j) {
            if(df[j][j+i] < M) {
                dp[i][j] += 
            }
        }
    }
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            printf("%d ", df[i][j]);
        }
        printf("\n");
    }
}

/*
  5 2 7 6
5 0 0 0 0
2 0 0 0 0
7 1 0 0 0
6 8 2 1 0

1 2 5 20 21
0 1 2 4 
0 0 


*/