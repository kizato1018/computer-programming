#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    while(n--) {
        int k;
        int a[100] = {};
        int cnt = 0;
        scanf("%d", &k);
        for(size_t i = 0; i < k; ++i) {
            scanf("%d", &a[i]);
        }
        for(size_t i = 0; i < k; ++i) {
            for(size_t j = i+1; j < k; ++j) {
                if(a[j-1] > a[j]) {
                    swap(a[j-1], a[j]);
                    cnt++;
                }
            }
        }
        printf("Optimal train swapping takes %d swaps.\n", cnt);
    }
}
