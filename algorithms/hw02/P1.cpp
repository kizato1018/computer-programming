#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <vector>
#define N 200001

using namespace std;

int main() {
    int n;
    int64_t arr[N] = {};
    vector<int> v;
    int Max = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%ld", &arr[i]);
    for(int i = n-1; i >= 0; i--) {

    }
    printf("%d\n", Max);
}
// 10
// 89 7 22 35 4 11 23 90 55 64