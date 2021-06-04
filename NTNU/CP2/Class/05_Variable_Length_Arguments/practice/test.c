#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

void f(int32_t arg1, int32_t arg2, int32_t arg3, int32_t arg4) {
    printf("arg1:%2d size:%2ld address:%p\n", arg1, sizeof(arg1), &arg1);
    printf("arg2:%2d size:%2ld address:%p\n", arg2, sizeof(arg2),&arg2);
    printf("arg3:%2d size:%2ld address:%p\n", arg3, sizeof(arg3),&arg3);
    printf("arg4:%2d size:%2ld address:%p\n", arg4, sizeof(arg4),&arg4);
}

int main() {
    f(1,2,3,4);
}