#include <stdio.h>
#include <stdint.h>

int main() {
    FILE *inputF = NULL;
    FILE *outputF = NULL;
    FILE *keyF = NULL;
    char inputName[256] = {}, outputName[256] = {}, keyName[256] = {};
    int8_t mode = 0;
    int8_t Map[26] = {};
    printf("Please enter the input file: ");
    scanf("%s", inputName);
    printf("Please enter the output file: ");
    scanf("%s", outputName);
    printf("Please enter the key file: ");
    scanf("%s", keyName);
    printf("Encryption (1) or Decryption (2): ");
    scanf("%hhd", &mode);
    if((inputF = fopen(inputName, "r")) == NULL) {
        printf("input file open failed\n");
        return 0;
    }
    if((outputF = fopen(outputName, "w")) == NULL) {
        printf("output file open failed\n");
        return 0;
    }
    if((keyF = fopen(keyName, "r")) == NULL) {
        printf("key file open failed\n");
        return 0;
    }
    if(mode != 1 && mode != 2) {
        printf("wrong mode\n");
        return 0;
    }

    char a, b, c;
    int i;
    while(!feof(keyF)) {
        if(mode == 1)
            fscanf(keyF, "%c : %c", &a, &b);
        else if(mode == 2)
            fscanf(keyF, "%c : %c", &b, &a);
        a = (a>='A' && a<='Z') ? a-'A' : a-'a';
        b = (b>='A' && b<='Z') ? b-'A' : b-'a';
        Map[a] = b-a;
    }

    while((c = fgetc(inputF)) != EOF) {
        i = (c>='A' && c<='Z') ? c-'A': c-'a';
        fputc(c+Map[i], outputF);
    }
    printf("Done!\n");
    fclose(inputF);
    fclose(outputF);
    fclose(keyF);
}