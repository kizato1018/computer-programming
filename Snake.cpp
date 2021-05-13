1#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include <windows.h>
#include<time.h>
char map[20][20]={0};
char Omap[20][20]={0};
int snake[400][2]={0};
int score=0,Gstart=clock(),Time=0;
void gotoxy(int xpos, int ypos)
{
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = xpos; scrn.Y = ypos;
  SetConsoleCursorPosition(hOuput,scrn);
}
char turn(int sec,char last) {
    int start=clock(),a;
    int end;
    char temp=last;
    while(1){
        if(kbhit()){
            a=getch();
            if(a==224){
                a=getch();
                switch(a){
                    case 72:
                        if(temp!='D')
                            last='U';
                        else
                            last='D';
                        break;
                    case 80:
                        if(temp!='U')
                            last='D';
                        else
                            last='U';
                        break;
                    case 75:
                        if(temp!='R')
                            last='L';
                        else
                            last='R';
                        break;
                    case 77:
                        if(temp!='L')
                            last='R';
                        else
                            last='L';
                        break;
                    default:
                        break;
                }
            }
        }
        end=clock();
        if((end-start)>=sec)
            return last;
    }
}
void pr_map(int x,int D,int J,int I){
    int i,j;
    HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
    WORD wOldColorAttrs;
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(h, &csbiInfo);
    wOldColorAttrs = csbiInfo.wAttributes;
    Time=(clock()-Gstart)/1000;
    //system("cls");
    SetConsoleTextAttribute ( h, 7 | FOREGROUND_INTENSITY );
    gotoxy(0,0);
    printf("Score:%d  Time:%d\n",score,Time/2);
    if(D!=3)
        for(i=0;i<20;i++){
            for(j=0;j<20;j++){
                if(map[j][i]=='*'){
                    SetConsoleTextAttribute ( h, x | FOREGROUND_INTENSITY );
                }
                else if(map[j][i]=='o')
                    SetConsoleTextAttribute ( h, 0 | FOREGROUND_INTENSITY );
                else
                    SetConsoleTextAttribute ( h, 7 | FOREGROUND_INTENSITY );
                if(Omap[j][i]!=map[j][i]){
                    gotoxy(j*2,i+1);
                    printf("%c ",map[j][i]);
                }

            }
            printf("\n");
        }

        else{
        for(i=0;i<20;i++){
            for(j=0;j<20;j++){
                if(map[j][i]=='*'){
                    SetConsoleTextAttribute ( h, x+16 | FOREGROUND_INTENSITY );
                    printf("%c ",map[j][i]);
                }
                if((i<=I+1 && i>=I-1 && j<=J+1 && j>=J-1) || (i==I && (j==J+2 || j==J-2)) || (j==J && (i==I+2 || i==I-2))){
                    if(map[j][i]!='*'){
                        if(map[j][i]=='o')
                            SetConsoleTextAttribute ( h, 16 | FOREGROUND_INTENSITY );
                        else
                            SetConsoleTextAttribute ( h, 23 | FOREGROUND_INTENSITY );
                        printf("%c ",map[j][i]);
                    }
                }
                else if(i%19==0 || j%19==0){
                    SetConsoleTextAttribute ( h, 7 | FOREGROUND_INTENSITY );
                    printf("%c ",map[j][i]);
                }
                else
                    if(map[j][i]!='*'){
                        SetConsoleTextAttribute ( h, 0 | FOREGROUND_INTENSITY );
                        printf("  ");
                    }
            }
            printf("\n");
            SetConsoleTextAttribute ( h, 7 | FOREGROUND_INTENSITY );
        }
    }
    /*else{

        for(i=0;i<20;i++){
            for(j=0;j<20;j++){
                if(Omap[j][i]!=map[j][i]){
                    if(map[j][i]=='*'){
                        SetConsoleTextAttribute ( h, x+16 | FOREGROUND_INTENSITY );
                        gotoxy(j*2,i+1);
                        printf("%c ",map[j][i]);
                    }
                    if(i==I && j==J)
                        for(int a=I-2;a<I+3;a++)
                            for(int b=J-2;b<J+3;b++){
                                if(a>0 && a<19 && b>0 && b<19 && ((a<=I+1 && a>=I-1 && b<=J+1 && b>=J-1) || (a==I && (b==J+2 || b==J-2)) || (b==J && (a==I+2 || a==I-2)))){
                                    if(map[b][a]!='*'){
                                        if(map[b][a]=='o')
                                            SetConsoleTextAttribute ( h, 16 | FOREGROUND_INTENSITY );
                                        else
                                            SetConsoleTextAttribute ( h, 23 | FOREGROUND_INTENSITY );
                                        gotoxy(b*2,a+1);
                                        printf("%c ",map[b][a]);
                                    }
                                }
                            }
                    else if(i%19==0 || j%19==0){
                        SetConsoleTextAttribute ( h, 7 | FOREGROUND_INTENSITY );
                        gotoxy(j*2,i+1);
                        printf("%c ",map[j][i]);
                    }
                    else
                        if(map[j][i]!='*'){
                            SetConsoleTextAttribute ( h, 0 | FOREGROUND_INTENSITY );
                                gotoxy(j*2,i+1);
                                printf("  ");
                            }
                }
            }
            printf("\n");
            SetConsoleTextAttribute ( h, 7 | FOREGROUND_INTENSITY );
        }
    }*/
    for(i=0;i<20;i++)
        for(j=0;j<20;j++)
            Omap[j][i]=map[j][i];
}

void Setup(){
    int i,j;
    Time=0;
    for(i=0;i<20;i++)
        for(j=0;j<20;j++){
            if(i==0 || i==19)
                map[i][j]='X';
            if(j==0 || j==19)
                map[i][j]='X';
        }
    for(i=0;i<3;i++){
        snake[i][0]=9;
        snake[i][1]=i+5;
        map[snake[i][1]][snake[i][0]]='o';
    }
    map[snake[2][1]][snake[2][0]]='O';
    /*
    printf("\n");
    for(i=0;i<20;i++){
        for(j=0;j<20;j++){
            Omap[j][i]=map[j][i];
            printf("%c ",map[j][i]);
        }
        printf("\n");
    }
    */
    score=0;
    Time=0;
    Gstart=clock();
}
int main(){
    start:
    char last='R',x='0',a,title[5][100]={{" "},{"   Snake!!\n    Easy"},{"   Snake!!\n   Normal"},{"   Snake!!\n    Hard"},{"   Snake!!\n    Extra"}};
    int length=3,flag=0,pt[3],i=1,wall[3]={0,0,0},tmp,difficulty[4]={300,200,100,150},D=0;


    do{
        printf("%s\n",title[i]);
        printf("Press space to start!");
        a=getch();
        switch(a){
            case 72:
                i--;
                break;
            case 80:
                i++;
                break;
            default:
                break;
        }
        if(i==0)
            i=4;
        else if(i==5)
            i=1;
        system("cls");
    }while(a!=' ');
    D=i-1;
    memset(map,' ',sizeof(map));
    memset(Omap,' ',sizeof(map));
    srand((unsigned)time(NULL));
    Setup();
    pt[2]=0;
    //map[1][1]='X';
    while(flag==0){
        while(pt[2]==0){
            pt[0]=rand()%18+1;
            pt[1]=rand()%18+1;
            if(map[pt[0]][pt[1]]==' '){
                map[pt[0]][pt[1]]='*';
                pt[2]=1;
                tmp=Time;
            }
        }
        pr_map(((pt[0]+pt[1])%6)+2,D,snake[length-1][1],snake[length-1][0]);
        last=turn(difficulty[D],last);
        switch(last){
            case 'U':
                snake[length][1]=snake[length-1][1];
                snake[length][0]=snake[length-1][0]-1;
                break;
            case 'D':
                snake[length][1]=snake[length-1][1];
                snake[length][0]=snake[length-1][0]+1;
                break;
            case 'L':
                snake[length][1]=snake[length-1][1]-1;
                snake[length][0]=snake[length-1][0];
                break;
            case 'R':
                snake[length][1]=snake[length-1][1]+1;
                snake[length][0]=snake[length-1][0];
                break;
            default:
                printf("error\n");
                break;
        }
        map[snake[0][1]][snake[0][0]]=' ';
        if(map[snake[length][1]][snake[length][0]]=='X' || map[snake[length][1]][snake[length][0]]=='o')
            flag=1;
        else if(map[snake[length][1]][snake[length][0]]=='*'){
            map[snake[0][1]][snake[0][0]]='o';
            for(i=1;i<=length;i++){
                map[snake[i][1]][snake[i][0]]='o';
            }
            length++;
            score+=10;
            for(i=0;i<=score/100;i++,wall[2]=0)
                while(wall[2]==0){
                    wall[0]=rand()%18+1;
                    wall[1]=rand()%18+1;
                    if(map[wall[0]][wall[1]]==' '){
                        map[wall[0]][wall[1]]='X';
                        wall[2]=1;
                    }
                }
            pt[2]=0;
        }
        else if(Time-tmp==20){
            while(wall[2]==0){
                wall[0]=rand()%18+1;
                wall[1]=rand()%18+1;
                if(map[wall[0]][wall[1]]==' '){
                    map[wall[0]][wall[1]]='X';
                    wall[2]=1;
                }
            }
            map[pt[0]][pt[1]]=' ';
            pt[2]=0;
        }
        else
            for(i=1;i<=length;i++){
                map[snake[i][1]][snake[i][0]]='o';
                snake[i-1][1]=snake[i][1];
                snake[i-1][0]=snake[i][0];
            }
        map[snake[length-1][1]][snake[length-1][0]]='O';
    }
    printf("Game Over\nTry Again:1  Quit:2\n");
    scanf(" %c",&x);
    system("cls");
    if(x=='1')
        goto start;
    else
        return 0;
}
