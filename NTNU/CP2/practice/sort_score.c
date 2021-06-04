#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct Student
{
    int ID;
    char Name[32];
    int32_t Score;
}student;

void sort(student s[], size_t n) {
    student tmp;
    for(size_t i = 0; i < n; i++) {
        for(size_t j = 1; j < n; j++) {
            if(s[j].Score > s[j-1].Score) {
                tmp = s[j];
                s[j] = s[j-1];
                s[j-1] = tmp;
            }
        }
    }
}

int main() {
    FILE *pFin = NULL;
    FILE *pFout = NULL;
    student students[100];
    size_t n = 0;
    
    pFin = fopen("score.txt", "r");
    pFout = fopen("sort_score.txt", "w");

    while(!feof(pFin)) {
        fscanf(pFin, "%u%31s%u", &students[n].ID, students[n].Name, &students[n].Score);
        n++;
    }

    sort(students, n);
    
    for(size_t i = 1; i <= n; i++)
        fprintf(pFout, "%02d %-31s %d\n", students[i-1].ID, students[i-1].Name, students[i-1].Score);

    fclose(pFin);
    fclose(pFout);
}