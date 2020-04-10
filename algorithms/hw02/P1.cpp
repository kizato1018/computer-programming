#include <cstdio>
#include <cstdint>
#include <algorithm>
#define N 200001

using namespace std;

int main() {
    int n;
    int64_t arr[N] = {};
    int64_t fin[N] = {};
    int64_t Max = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%ld", &arr[i]);
        fin[i] = arr[i];
    }
    stable_sort(fin, fin+n);
    for(int i = n-1; i >= 0; i--) {
        Max = max(Max, i-(find(fin, fin+i, arr[i])-fin));
    }
    printf("%ld\n", Max);
}
// 10
// 89 7 22 35 4 11 23 90 55 64