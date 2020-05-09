#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

struct A {
    int start = 0;
    int end = 0;
    int cnt = 0;
};

bool cmp(A a, A b) {
    if(a.end < b.end) return true;
    else if (a.end == b.end) return a.start > b.start;
    return false;
}

int main() {
    int N = 0;
    A a[100010];
    int firework[300010] = {0};
    int count = 0;
    scanf("%d", &N);
    for(int i = 0; i < N; ++i) {
        scanf("%d %d", &a[i].start, &a[i].end);
    }
    sort(a, a+N, cmp);
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < 2; ++j) {
            if(count > j && a[i].start <= firework[count-1-j])
                ++a[i].cnt;
        }
        
        for(int j = 0; a[i].cnt < 2; ++j) {
            // printf("%d ", a[i].end-j);
            firework[count] = a[i].end-j;
            ++count;
            ++a[i].cnt;
        }
    }
    printf("%d", count);
    return 0;
}