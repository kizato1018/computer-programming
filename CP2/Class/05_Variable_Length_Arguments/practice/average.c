#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

double avg(int32_t arg1, ...) {
    va_list ap;
    double result = 0;
    size_t cnt = arg1;
    va_start(ap, arg1);
    for(size_t i = 0; i < cnt; ++i) {
        result += va_arg(ap, int32_t);
    }
    return result/cnt;
}

int main() {
    printf("avg: %lf\n", avg(5,1,1,1,1,1));
}