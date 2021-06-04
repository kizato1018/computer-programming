#include <stdio.h>

int main()
{
    char arr[4] = {'A', 'B', 'C', 'D'};
    char tab[3][2] = {{'E', 'F'}, {'G', 'H'}, {'I', 'J'}};
    char *p = arr+1;
    char *mp[2]={arr, tab[2]};
    char **pp = &p, **qq = mp;
    char (*s)[2] = tab;
    printf("%c\n", s[0][1]);
    printf("%c", s[1][0]);

}