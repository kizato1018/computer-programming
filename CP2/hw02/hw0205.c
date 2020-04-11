#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main() {
    FILE *confF = NULL;
    FILE *tmpF = NULL;
    char confName[256] = {}; 
    char option[256] = {};
    char value[256] = {};
    char context[1024] = {};
    bool flag = true;
    printf("Please enter the configuration file: ");
    scanf("%s", confName);
    printf("Option: ");
    scanf("%s", option);
    printf("Value: ");
    scanf("%s", value);
    if((confF = fopen(confName, "r+")) == NULL) {
        printf("configuration file open failed\n");
        return 0;
    }
    if((tmpF = fopen("temp.conf", "w+")) == NULL) {
        printf("temp file open failed\n");
        return 0;
    }
    while(!feof(confF)) {
        fgets(context, sizeof(context), confF);
        if(context[0] == '#'){
            fputs(context, tmpF);
        }
        else {
            if(strncmp(option, context, strlen(option))){
                fputs(context, tmpF);
            }
            else {
                fprintf(tmpF, "%s=%s\n", option, value);
                flag = false;
            }
        }    
    }
    if(flag) {
        fprintf(tmpF, "%s=%s", option, value);
    }

    rewind(confF);
    rewind(tmpF);
    while(!feof(tmpF)){
        fgets(context, sizeof(context), tmpF);
        fputs(context, confF);
    }
    printf("Done!\n");
}