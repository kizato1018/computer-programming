#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define GREEN "\033[0;32;32m"
#define BLUE "\033[0;32;34m"
#define PURPLE "\033[0;32;35m"
#define Yellow "\033[0;32;33m"
#define RESET "\033[m"
#define print(color, str) printf(color"%s"RESET, str)

char keyWord[][256] = {"break", "case", "char", "const",
                       "continue", "default", "do", "double",
                       "else", "enum", "extern", "float",
                       "for", "goto", "if", "long",
                       "return", "short", "signed", "sizeof",
                       "static", "struct", "switch", "typedef",
                       "uint8_t", "uint16_t", "uint32_t", "uint64_t",
                       "int8_t", "int16_t", "int32_t", "int64_t",
                       "int", "union", "unsigned", "void", "while"};

int8_t color[] = {2, 2, 2, 2, 1, 1, 1, 2,
                  1, 2, 1, 1, 2, 2, 2, 1,
                  2, 1, 1, 2, 1, 1, 2, 1,
                  0, 0, 0, 0, 0, 0, 0, 0,
                  1, 1, 1, 1, 2};

char filiter[] = "abcdefghijklmnopqrstuvwxyz0123456789_";

void HighLight(char *str) {
    int cnt = 0;
    char tmp[64] = {};
    bool f = false;
    for(int i = 0; i < strlen(str); i++) {
        if(strchr(filiter, str[i]) == NULL) {
            for(int j = 0; keyWord[j][0]; j++) {
                if(strcmp(tmp, keyWord[j]) == 0) {
                    if(color[j] == 0) 
                        print(GREEN, tmp);
                    else if(color[j] == 1) 
                        print(BLUE, tmp);
                    else if(color[j] == 2) 
                        print(PURPLE, tmp);
                    f = true;
                    break;
                }
            }
            if(!f) 
                printf("%s", tmp);
            if(str[i] == '(' || str[i] == ')' || str[i] == '[' || str[i] == ']' || str[i] == '{' || str[i] == '}') 
                printf(Yellow"%c"RESET, str[i]);
            else printf("%c", str[i]);
            memset(tmp, 0, sizeof(tmp));
            cnt = 0;
            f = false;
        }
        else 
            tmp[cnt++] = str[i];
    }
}

int main() {
    FILE *cF;
    char fileName[256] = {};
    char context[1024] = {};
    printf("Please enter the C file: ");
    scanf("%s", fileName);
    if(strstr(fileName, ".c") == NULL) {
        printf("This is not a C file\n");
        return 0;
    }
    if((cF = fopen(fileName, "r")) == NULL) {
        printf("C file open failed\n");
        return 0;
    }
    while(fgets(context, sizeof(context), cF) != NULL) 
        HighLight(context);
    fclose(cF);
}