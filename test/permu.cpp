#include <cstdio>
#include <algorithm>

void print(int a[], int n) {
    for(int i = 0; i < n; ++i)
        printf("%d ", a[i]);
    printf("\n");
}

void gen(int a[], int n, int s) {
    if(s == n) {
        printf("ans:");
        print(a, n);
    }
    else {
        for(int i = s; i < n; ++i) {
            std::swap(a[s], a[i]);
            printf("s=%d, i=%d ", s, i);
            print(a, n);
            gen(a, n, s+1);
        }
    }
    return;
}

int main() {
    int a[] = {3, 1, 4};
    gen(a, 3, 0);
    return 0;
}