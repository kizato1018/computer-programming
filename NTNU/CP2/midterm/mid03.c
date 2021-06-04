#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

typedef struct _Date{
    int year;
    int month;
    int day;
    int hr;
    int min;
    int sec;
    char other[256];
}Date;

typedef struct _Commit{
    char user[256];
    Date date;
    int32_t revision;
    char file[256][1024];
    
}Commit;

void getDate(char *s, Date *d) {
    d->year = atoi(strtok(s, "- :"));
    d->month = atoi(strtok(NULL, "- :"));
    d->day = atoi(strtok(NULL, "- :"));
    d->hr = atoi(strtok(NULL, "- :"));
    d->min = atoi(strtok(NULL, "- :"));
    d->sec = atoi(strtok(NULL, "- :"));
}

int main() {
    char fName[256] = {};
    FILE *pFile = NULL;
    printf("Please enter the mbox file: ");
    scanf("%s", fName);
    if( ( pFile = fopen( fName, "rb" ) ) == NULL ) {
        printf( "File could not be opened!\n" );
        return 0;
    }
    
    Commit commit[1024];
    size_t count = 0;
    size_t cfile = 0;
    bool flag = false;
    while(!feof(pFile)) {
        char context[1024];
        fgets(context, sizeof(context), pFile);
        if(context[strlen(context)-1] == '\n') context[strlen(context)-1] = 0;
        if(flag) {
            if(strstr(context, "Log: ") == NULL)
                strcpy(commit[count].file[cfile++], context);
            else {
                flag = false;
                cfile = 0;
            }
        }
        else if(strstr(context, "Author: ") != NULL) {
            strcpy(commit[count].user, context+8);
        }
        else if(strstr(context, "Date: ") != NULL) {
            getDate(context+6, &(commit[count].date));
        }
        else if(strstr(context, "New Revision: ") != NULL) {
            commit[count].revision = atoi(context+14);
        }
        else if(strstr(context, "Modified: ") != NULL) {
            flag = true;
        }
    }

}