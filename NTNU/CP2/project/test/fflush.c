#include <stdio.h>
#include <unistd.h>

int main() {
    char str[1024];
    while(1) {
        printf("please type.\n");
        fgets(str, sizeof(str), stdin);
        printf("wait\n");
        sleep(3);
        printf("you type:%s", str);
        while(!feof(stdin)) getc(stdin);
    }
}