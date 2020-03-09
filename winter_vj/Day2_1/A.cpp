#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;
int Adjacency_Matrix[105][105];
bool vist[105];
void dfs(int s, int n)
{
    for(int i = 1; i <= n; i++)
        if(Adjacency_Matrix[s][i] && !vist[i]){
            vist[i] = true;
            dfs(i, n);
        }
}
int main()
{
    int n;
    while (scanf("%d",&n) == 1 && n)
    {
        memset(Adjacency_Matrix, 0, sizeof(Adjacency_Matrix));
        int a, b;
        while (scanf("%d", &a) == 1 && a)
        {
            while (scanf("%d", &b) == 1 && b)
            {
                Adjacency_Matrix[a][b] = 1;
            }
        }
        int m;
        scanf("%d", &m);
        for (int i = 0 ; i < m ; ++i)
        {
            memset(vist, 0, sizeof(vist));
            int start = 0;
            scanf("%d", &start);
            dfs(start, n);
            int count = 0;
            for (int j = 1 ; j <= n ; ++j)
            {
                if(!vist[j])
                {
                    count += 1;
                }
            }
            printf("%d", count);
            for (int j = 1 ; j <= n ; ++j)
            {
                if (!vist[j])
                {
                    printf(" %d", j);
                }
            }
            printf("\n");
        }
    }
}