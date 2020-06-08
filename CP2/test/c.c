#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int a = 0;
    scanf("%d", &a);
    switch (a) {
    case 0 ... 20:
        printf("Ok\n");
        break;
    case 21 ... 40:
        printf("Good\n");
        break;
    
    default:
        break;
    }
}