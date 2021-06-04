#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define GREEN "\033[0;32;32m"
#define BLUE "\033[0;32;34m"
#define PURPLE "\033[0;35m"
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

char check[] = " \t()[]{};,?:";

void HighLight(char *str) {
    int i = -1, pos = 0, len = 0, cnt = 0, L = strlen(str);
    char *p;
    while(keyWord[++i][0]) {
        pos = 0;
        while((pos < L) && (p = strstr(str+pos, keyWord[i])) != NULL) {
            char tmp[1024] = {};
            cnt = p-str;
            len = strlen(keyWord[i]);
            if(!strncmp(p+len, RESET, 3)) break;
            if(cnt > 0 && strchr(check, p[-1]) == NULL) break;
            strncpy(tmp, str, cnt);
            if(color[i] == 0) {
                strcat(tmp, GREEN);
                cnt += 11;
            }
            else if(color[i] == 1) {
                strcat(tmp, BLUE);
                cnt += 11;
            }
            else if(color[i] == 2) {
                strcat(tmp, PURPLE);
                cnt += 8;
            }
            strcat(tmp, keyWord[i]);
            strcat(tmp, RESET);
            cnt += len + 4;
            strcat(tmp, p+len);
            strcpy(str, tmp);
            pos = cnt;
            cnt = 0;
        }
    }
    for(int i = 0; i < strlen(str); i++) {
        if(str[i] == '(' || str[i] == ')' || str[i] == '[' || str[i] == ']' || str[i] == '{' || str[i] == '}'){
            if((i>0) && (str[i-1] != '\033'))
                printf(PURPLE"%c"RESET, str[i]);
            else
                printf("%c", str[i]);
        }
        else
            printf("%c", str[i]);
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