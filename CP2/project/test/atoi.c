#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char str[100] = {};
    int a;
    // char* token = strtok(str, " \n");
    for(int i = 0; i < 5; ++i) {
        sprintf(str, "%d ", i);
        // sscanf(str, "%s", tmp);
        // a = atoi(token);
        printf("%s\n", str);
        // token = strtok(NULL, " \n");
    }
}