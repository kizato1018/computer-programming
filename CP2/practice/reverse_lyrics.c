#include <stdio.h>
#include <string.h>

typedef struct String
{
    char words[256];
}string;


int main() {
    FILE *pFin = NULL;
    FILE *pFout = NULL;
    string l[512];
    
    size_t n = 0;
    pFin = fopen("lyrics.txt", "r");
    pFout = fopen("lyrics_revers.txt", "a");
    while(!feof(pFin)) {
        char words[512] = {};
        fgets(words, sizeof(words), pFin);
        //fgets(l[n].words, sizeof(l[n].words), pFin);
        //if(l[n].words[strlen(l[n].words)-1] == '\n') l[n].words[strlen(l[n].words)-1] = '\0';
        fprintf(pFout, "%d %s", n+1, words);
        fseek(pFout, 0, SEEK_SET);
        //rewind(pFout);
        printf("%ld\n", ftell(pFout));
        n++;
    }
    while(n--) {
        //fprintf(pFout, "%s\n", l[n].words);
    }
    fclose(pFin);
    fclose(pFout);

}