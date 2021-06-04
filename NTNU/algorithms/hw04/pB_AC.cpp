#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct A {
    int start = 0;
    int end = 0;
    int cnt = 0;
};

bool cmp(A a, A b) {
    if(a.end < b.end) return true;
    else if (a.end == b.end) return a.start > b.start;
    else return false;
}

int main() {
    int N;
    A a[100010];
    int firework[200020] = {0};
    int count = 0;
    scanf("%d", &N);
    for(int i = 0; i < N; ++i) {
        scanf("%d %d", &a[i].start, &a[i].end);
    }
    sort(a, a+N, cmp);
    for(int i = 0; i < N; ++i) {
        for(int j = count-1; j >= 0; --j) {
            if(a[i].cnt < 2) {
                if(a[i].start <= firework[j]) 
                    ++a[i].cnt;
                else if(j > 1 &&a[i].start > firework[j-1])
                    break;
            }
            else
                break;
        }
        for(int j = 0; a[i].cnt < 2; ++j) {
            // printf("%d ", a[i].end-j);
            firework[count] = a[i].end-j;
            ++count;
            ++a[i].cnt;
        }
    }
    printf("%d", count);
}