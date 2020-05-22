#include <stdio.h>
#define FOR_EACH_STEP(i, begin, end, n) for(int i = begin; i < end; i+=n)
#define FOR_EACH(i, begin, end) FOR_EACH_STEP(i, begin, end, 1)
#define SUM_OF_ARRAY(sum, array, n) FOR_EACH(i, 0, n) sum += array[i];

int main() {
    int sum = 0;
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    FOR_EACH(i, 0, 10) {
        printf("%d ", arr[i]);
    }
    puts("");
    FOR_EACH_STEP(i, 0, 10, 2) {
        printf("%d ", arr[i]);
    }
    puts("");
    FOR_EACH(i, 0, 10) {
        FOR_EACH_STEP(j, i, 10, 2) {
            printf("%d ", arr[j]);
        }
        puts("");
    }
    SUM_OF_ARRAY(sum, arr, 10);
    printf("%d\n", sum);
}