#include <stdio.h>
#include <stdint.h>
#include <string.h>

void printHex(uint8_t data[], uint32_t count) {
    printf("%07x", count);
    for(size_t i = 0; i < 16; i += 2) {
        printf(" %02x%02x", data[i], data[i+1]);
    }
    printf("\n");
}

int main() {
    FILE *pF = NULL;
    char input[256] = {};
    uint32_t count = 0;
    printf("Please enter the file: ");
    fgets(input, sizeof(input), stdin);
    if(input[strlen(input)-1] == '\n')
        input[strlen(input)-1] = 0;
    if((pF = fopen(input, "rb")) == NULL) {
        printf("open file error\n");
        return 1;
    }
    while(!feof(pF)) {
        uint8_t data[16] = {};
        fread(data, 1, 16, pF);
        printHex(data, count);
        count += 16;
    }
    
}