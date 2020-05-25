#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main( int argc, char *argv[] ) {
    FILE *pF = NULL;
    char context[1024] = {};
    char *filename = NULL; 
    int32_t col[256] = {};
    int32_t col_num = 0;
    char *string[64] = {};
    int32_t string_num = 0;
    int8_t flag = 0;
    char *separator = " ";
    int8_t format[64] = {};
    int8_t format_cnt = 0;


    for(int i = 1; i < argc; ++i) {
        if(i == argc-1) {
            filename = argv[i];
        }
        else if(argv[i][0] == '-' && i == 1) {
            if(argv[i][1] == 'F') {
                flag = 1;
                ++i;
                separator = argv[i];
                continue;
            }
            else{
                printf("no this option\n");
                return 1;
            }
        }
        else if(argv[i][0] == '$') {
            col[col_num] = argv[i][1] - '0';
            ++col_num;
            format[format_cnt] = 1;
            ++format_cnt;
        }
        else {
            string[string_num] = argv[i];
            ++string_num;
            format[format_cnt] = 2;
            ++format_cnt;
        }
    }

    if((pF = fopen(filename, "r")) == NULL) {
        perror("open file error.\n");
        return 1;
    }

    
    while(fgets(context, sizeof(context), pF)) {
        // printf("%s", context);
        if(context[strlen(context)-1] == '\n')
            context[strlen(context)-1] = 0;
        int c = 0;
        char *data[64] = {};
        data[c] = strtok(context, separator);
        while(data[c] != NULL) {
            ++c;
            data[c] = strtok(NULL, separator);
        }
        c = 0;
        int32_t s = 0;
        for(size_t i = 0; i < format_cnt; ++i) {
            if(format[i] == 1) {
                printf("%s", data[col[c]-1]);
                ++c;
            }
            else if(format[i] == 2) {
                printf("%s", string[s]);
                ++s;
            }
        }
        printf("\n");
    }
    
    fclose(pF);
    return 0;
}