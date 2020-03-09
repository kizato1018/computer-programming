#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
int Adjacency_Matrix[105][105] = {};
int sum=0;
int y_length = 0;
int x_length = 0;
void dfs(int x, int y)
{
    if(Adjacency_Matrix[x][y]) return;
    Adjacency_Matrix[x][y] = 1;
    sum++;
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}
int main()
{
    int time;
    cin >> time;
    for(int t = 0; t < time; t++)
    {
        if(t)
        {
            printf("\n");
        }
        memset(Adjacency_Matrix, 1, sizeof(Adjacency_Matrix));
        int input_x, input_y;
        cin >> input_x >> input_y;
        getchar();
        string s;
        sum = 0;
        x_length = 0;
        y_length = 0;
        while(getline(cin,s)&&s!="")
        {
            y_length = s.size();
            x_length++;
            for(int i = 1; i <= s.size(); i++)
            {
                Adjacency_Matrix[x_length][i] = s[i-1] - '0';
            }
        }
        dfs(input_x, input_y);
        cout << sum << endl;
    }
}