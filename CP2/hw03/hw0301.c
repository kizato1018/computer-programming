#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

// typedef struct _Data{
//     char date[10];
//     char Home[32];
//     char Away[32];
//     int FTHG;
//     int 
// }Data;

typedef struct _Team{
    char Name[64];
    int32_t Point;
    int32_t Win;
    int32_t Draw;
    int32_t Lose;
    int32_t Position;
}Team;

int cmp(const void *a, const void *b) {
      return ((*(Team *)b).Point - (*(Team *)a).Point);
}

void printTeam(Team T) {
    printf("Name: %s\n", T.Name);
    printf("Points:    %d\n", T.Point);
    printf("Win:       %d\n", T.Win);
    printf("Draw:      %d\n", T.Draw);
    printf("Lose       %d\n", T.Lose);
    if(T.Position % 10 == 1 && T.Position % 100 != 11)
        printf("Position:  %dst\n", T.Position);
    else if(T.Position % 10 == 2 && T.Position % 100 != 12)
        printf("Position:  %dnd\n", T.Position);
    else if(T.Position % 10 == 3 && T.Position % 100 != 13)
        printf("Position:  %drd\n", T.Position);
    else
        printf("Position:  %dth\n", T.Position);
}

Team teams[200];
int count = 0;

void score(size_t Win, size_t Lose, bool Draw) {
    if(Draw) {
        teams[Win].Point += 1;
        teams[Lose].Point += 1;
        ++teams[Win].Draw;
        ++teams[Lose].Draw;
    }
    else {
        teams[Win].Point += 3;
        ++teams[Win].Win;
        ++teams[Lose].Lose;
    }
}

bool Read(FILE *pF) {
    char data[1024];
    char check[] = "Date,HomeTeam,AwayTeam,FTHG,FTAG,FTR,HTHG,HTAG,HTR,Referee,HS,AS,HST,AST,HF,AF,HC,AC,HY,AY,HR,AR\r\n";
    fgets(data, sizeof(data), pF);
    if(strcmp(data,check) != 0) {
        printf("Wrong file\n");
        return true;
    }
    int cnt = 0;
    while(!feof(pF)) {
        bool HomeExist = false, AwayExist = false;
        size_t Home = count, Away = count;
        fgets(data, sizeof(data), pF);
        char *token = strtok(data, ",");
        if((token = strtok(NULL, ",")) == NULL) 
            break;
        for(size_t i = 0; i < count; ++i) {
            if(strcmp(token, teams[i].Name) == 0) {
                Home = i;
                HomeExist = true;
            }
        }
        if(!HomeExist) {
            Home = count;
            strcpy(teams[Home].Name, token);
            ++count;
        }
        token = strtok(NULL, ",");
        for(size_t i = 0; i < count; ++i) {
            if(strcmp(token, teams[i].Name) == 0) {
                Away = i;
                AwayExist = true;
            }
        }
        if(!AwayExist) {
            Away = count;
            strcpy(teams[Away].Name, token);
            ++count;
        }
        token = strtok(NULL, ",");
        token = strtok(NULL, ",");
        token = strtok(NULL, ",");
        switch (*token) {
        case 'H':
            score(Home, Away, false);
            break;
        case 'A':
            score(Away, Home, false);
            break;
        case 'D':
            score(Home, Away, true);
            break;
        default:
            break;
        }
    }
    qsort(teams, count, sizeof(Team), cmp);
    for(size_t i = 0; i < count; ++i) {
        teams[i].Position = i+1;
        if(i > 0 && teams[i].Point == teams[i-1].Point)
            teams[i].Position = teams[i-1].Position;
    }
    return false;
}

int main() {
    FILE *pF = NULL;
    char input[256] = {};
    char name[64];
    bool isExist = false;
    printf("Please enter the season data file: ");
    fgets(input, sizeof(input), stdin);
    if(input[strlen(input)-1] == '\n')
        input[strlen(input)-1] = 0;
    if((pF = fopen(input, "r")) == NULL) {
        printf("open file error\n");
        return 1;
    }
    printf("Please enter Team Name: ");
    fgets(name, sizeof(name), stdin);
    if(name[strlen(name)-1] == '\n')
        name[strlen(name)-1] = 0;
    if(Read(pF)) {
        return 1;
    }
    for(size_t i = 0; i < count; ++i) {
        //if(strcmp(name, teams[i].Name) == 0) {
            printTeam(teams[i]);
            isExist = true;
        //}
    }
    if(!isExist) {
        printf("No such a team!\n");
    }

    

}