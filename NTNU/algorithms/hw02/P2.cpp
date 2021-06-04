#include <cstdio>
#include <cstdint>
#define N 200000

using namespace std;

int64_t cnt = 0;

void merge(int64_t a[], int64_t begin, int64_t mid, int64_t end) {
    static int64_t tmp[N];
    int64_t i = begin;
    int64_t j = mid+1;
    int64_t k = 0;
    while(i <= mid && j <= end) {
        if(a[i] <= a[j])
            tmp[k++] = a[i++];
        else {
            tmp[k++] = a[j++];
            cnt += mid - i + 1;
        }
    }
    while(i <= mid) tmp[k++] = a[i++];
    while(j <= end) tmp[k++] = a[j++];
    for(i = 0; i <= end-begin; i++)
        a[begin+i] = tmp[i];
    //printf("begin:%d end:%d cnt:%d\n", begin, end, cnt);
}


void merge_sort(int64_t a[], int64_t begin, int64_t end) {
    if(begin < end) {
        int64_t mid = (begin + end) / 2;
        merge_sort(a, begin, mid);
        merge_sort(a, mid+1, end);
        merge(a, begin, mid, end);
    }
}

int main() {
    int64_t n, num, j = 0, k = 0;
    int64_t even[N], odd[N];
    bool flag = true;
    scanf("%ld", &n);
    //printf("%d", n);
    for(int i = 0; i < n; i++) {
        scanf("%ld", &num);
        //printf("%d ", num);
        if(i%2) odd[j++] = num;
        else even[k++] = num;
    }
    merge_sort(odd, 0, j-1);
    merge_sort(even, 0, k-1);
    for(int i = 0; i < n/2; i++) {
        if(odd[i] < even[i]) {
            flag = false;
            break;
        }
        if(i+1 < k && even[i+1] < odd[i]) {
            flag = false;
            break;
        }
    }

    printf((flag) ? "yes\n" : "no\n");
    printf("%ld\n", cnt);
}