#include <stdio.h>
#include <stdint.h>

typedef struct Clock{
    int8_t hour;
    int8_t minute;
    int8_t second;
}clock;

int c2s(clock c) {
    return c.hour * 3600 + c.minute * 60 + c.second;
}

int sub(clock c1, clock c2) {  
    return (c2s(c1) > c2s(c2)) ? c2s(c1) - c2s(c2) : c2s(c2) - c2s(c1);
}

void input(clock *c) {
    printf("Please input hour: ");
    scanf("%hhd", &c->hour);
    printf("Please input minute: ");
    scanf("%hhd", &c->minute);
    printf("Please input second: ");
    scanf("%hhd", &c->second);
}

int main() {
    clock c1, c2;
    input(&c1);
    input(&c2);
    printf("difference: %d\n", sub(c1, c2));
}