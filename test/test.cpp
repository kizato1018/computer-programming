#include <bits/stdc++.h>

using namespace std;

int64_t N, sum = 0;
int64_t a[20];
bool DFS(int64_t i, int64_t A, int64_t B, int64_t C) {
    if(i == N) return (A == B) & (B == C);
    else if(A > sum/3 || B > sum/3 || C > sum/3) return 0;
    return DFS(i+1, A+a[i], B, C) | DFS(i+1, A, B+a[i], C) | DFS(i+1, A, B, C+a[i]); 
}
int main() {
    scanf("%lld", &N);
    for(int i = 0; i < N; ++i) {
        scanf("%lld", &a[i]);
        sum += a[i];
    }
    printf("%s", ((sum%3 == 0) & DFS(0, 0, 0, 0)) ? "YES" : "NO");
}