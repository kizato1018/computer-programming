#include <bits/stdc++.h>
using namespace std;

struct pos{
    int y, x;
};

pos P, B, T;
int N, M;
char Map[40][40] = {0};
int dx[] = {0, 1, 0, -1};
int dy[] = {-1, 0, 1, 0};
queue<pos> p;

bool pos_cmp(pos a, pos b) {return a.x == b.x & a.y == b.y;}
void ppos(pos a) {printf("(%d, %d)", a.x, a.y);}
void printMap() {
    puts("");
    for(int i = 0; i <= N+1; ++i) {
        for(int j = 0; j <= M+1; ++j) {
            printf("%c", Map[i][j]);

        }
        puts("");
    }
    puts("------------");
}
int BFS(pos start, pos goal, char obj) {
    queue<pos> q;
    int visited[40][40] = {0};
    pos cur, Pcur;
    int step = 0, cnt = 1, buf = 0;
    ++visited[start.y][start.x];
    q.push(start);
    // printf("%d, %d\n", q.front().x, q.front().y);
    while(!q.empty()) {
        if(pos_cmp(q.front(), goal)) return step;
        cur = q.front();
        if(obj == 'B') {
            Pcur = p.front();
            Map[cur.y][cur.x] = 'B';
            // ppos(cur);
            // printMap();
        }
        for(int i = 0; i < 4; ++i) {
            if(Map[cur.y+dy[i]][cur.x+dx[i]] == '.' && visited[cur.y+dy[i]][cur.x+dx[i]] < 10) {
                if(obj == 'B') {
                    if(BFS(Pcur, {cur.y-dy[i], cur.x-dx[i]}, 'P') == -1) continue;
                    p.push(cur);
                }
                else if(obj == 'P') {
                    if(pos_cmp({cur.y+dy[i], cur.x+dx[i]}, T)) continue;
                }
                q.push(pos{cur.y+dy[i], cur.x+dx[i]});
                ++visited[cur.y+dy[i]][cur.x+dx[i]];
                ++buf;
            }
        }
        q.pop();
        if(obj == 'B') {
            Map[cur.y][cur.x] = '.';
            p.pop();
        }
        if(--cnt == 0) {
            ++step;
            cnt = buf;
            buf = 0;
        }
    }
    return -1;
}

int main() {
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= N; ++i) {
        scanf("%s", Map[i]+1);
        for(int j = 1; j <= M; ++j) {
            // printf("[%c]", Map[i][j]);
            if(Map[i][j] == 'P') P = {i, j};
            else if(Map[i][j] == 'B') B = {i, j};
            else if(Map[i][j] == 'T') T = {i, j}; 
        }
    }
    for(int i = 0; i <= N+1; ++i) {
        Map[i][0] = '#';
        Map[i][M+1] = '#';
    }
    for(int i = 0; i <= M+1; ++i) {
        Map[0][i] = '#';
        Map[N+1][i] = '#';
    }
    // printMap();
    Map[P.y][P.x] = '.';
    Map[T.y][T.x] = '.';
    // printMap();
    p.push(P);
    printf("%d\n", BFS(B, T, 'B') );
}