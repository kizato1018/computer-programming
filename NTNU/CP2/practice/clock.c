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

clock sub(clock c1, clock c2) {  
    uint64_t d = (c2s(c1) > c2s(c2)) ? c2s(c1) - c2s(c2) : c2s(c2) - c2s(c1);
    return (clock) {.hour = d / 3600, .minute = (d %= 3600) / 60, .second = (d %= 60)};
}

void input(clock *c) {
    printf("Please input hour: ");
    scanf("%hhd", &c->hour);
    printf("Please input minute: ");
    scanf("%hhd", &c->minute);
    printf("Please input second: ");
    scanf("%hhd", &c->second);
}

void printd(const clock c) {
    printf("difference: %hhd:%hhd:%hhd\n", c.hour, c.minute, c.second);
}

int main() {
    clock c1, c2;
    input(&c1);
    input(&c2);
    printd(sub(c1, c2));
}