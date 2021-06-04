#include <iostream>
#include <queue>

using namespace std;

typedef struct _position {
    int32_t x;
    int32_t y;
}position;


int main() {
    int32_t n,m;
    cin >> n >> m;
    queue<position> q;
    queue<position> p;
    int32_t k = n*m;
    int32_t B_position[2] = {0};
    int32_t P_position[2] = {0};
    int32_t T_position[2] = {0};
    bool visited[35][35] = {false};
    char map[35][35] = {0};
    for(int32_t i = 1 ; i < n+1 ; i++) {
        for(int32_t j = 1 ; j < m+1 ; j++) {
            cin >> map[i][j];
            if(map[i][j] == 'B') {
                B_position[0] = i;
                B_position[1] = j;
            }
            else if(map[i][j] == 'P') {
                P_position[0] = i;
                P_position[1] = j;
            }
            else if(map[i][j] == 'T') {
                T_position[0] = i;
                T_position[1] = j;
            }
        }
    }
    // for(int32_t i = 1 ; i < n+1 ; i++) {
    //     for(int32_t j = 1 ; j < m+1 ; j++) {
    //         cout << map[i][j];
    //     }
    //     cout << endl;
    // }
    int32_t ans = 0;
    bool BT = false;
    q.push(position{B_position[0],B_position[1]});
    p.push(position{P_position[0],P_position[1]});
    for(int32_t i = 0 ; i < k ; i++) {
        position tmp = q.front();
        cout << map[tmp.x][tmp.y] << endl;
        ans ++;
        if(map[tmp.x][tmp.y] == 'T') {
            BT = true;
            break;
        }
        printf("%d, %d\n", tmp.x, tmp.y);
        printf("[%c]\n", map[tmp.x-1][tmp.y]);
        if(map[tmp.x-1][tmp.y] == '.') {
            printf("A\n");
            bool PB = false;
            for(int32_t j = 0 ; j < k ; j++) {
                position ptmp = p.front();
                if(ptmp.x == tmp.x+1 && ptmp.y == tmp.y){
                    PB = true;
                    break;
                }
                printf("n\n");
                if(map[ptmp.x-1][ptmp.y] == '.')
                    p.push(position{ptmp.x-1,ptmp.y});
                if(map[ptmp.x+1][ptmp.y] == '.')
                    p.push(position{ptmp.x+1,ptmp.y});
                if(map[ptmp.x][ptmp.y-1] == '.')
                    p.push(position{ptmp.x,ptmp.y-1});
                if(map[ptmp.x][ptmp.y+1] == '.')
                    p.push(position{ptmp.x,ptmp.y+1});
                p.pop();
                printf("a\n");
            }
            if(PB)
                q.push(position{tmp.x-1 , tmp.y});
        }
        if(map[tmp.x+1][tmp.y] == '.') {
            printf("B\n");
            bool PB = false;
            for(int32_t j = 0 ; j < k ; j++) {
                position ptmp = p.front();
                if(ptmp.x == tmp.x+1 && ptmp.y == tmp.y){
                    PB = true;
                    break;
                }
                if(map[ptmp.x-1][ptmp.y] == '.')
                    p.push(position{ptmp.x-1,ptmp.y});
                if(map[ptmp.x+1][ptmp.y] == '.')
                    p.push(position{ptmp.x+1,ptmp.y});
                if(map[ptmp.x][ptmp.y-1] == '.')
                    p.push(position{ptmp.x,ptmp.y-1});
                if(map[ptmp.x][ptmp.y+1] == '.')
                    p.push(position{ptmp.x,ptmp.y+1});
                p.pop();
            }
            if(PB)
                q.push(position{tmp.x+1 , tmp.y});
        }
        if(map[tmp.x][tmp.y-1] == '.') {
            printf("C\n");
            bool PB = false;
            for(int32_t j = 0 ; j < k ; j++) {
                position ptmp = p.front();
                printf("%d\n", p.size());
                if(ptmp.x == tmp.x && ptmp.y == tmp.y+1){
                    PB = true;
                    break;
                }
                if(map[ptmp.x-1][ptmp.y] == '.')
                    p.push(position{ptmp.x-1,ptmp.y});
                if(map[ptmp.x+1][ptmp.y] == '.')
                    p.push(position{ptmp.x+1,ptmp.y});
                if(map[ptmp.x][ptmp.y-1] == '.')
                    p.push(position{ptmp.x,ptmp.y-1});
                if(map[ptmp.x][ptmp.y+1] == '.')
                    p.push(position{ptmp.x,ptmp.y+1});
                p.pop();
            }
            if(p.empty()) printf("empty!\n");
            if(PB)
                q.push(position{tmp.x , tmp.y-1});
        }
        if(map[tmp.x][tmp.y+1] == '.') {
            printf("D\n");
            bool PB = false;
            for(int32_t j = 0 ; j < k ; j++) {
                position ptmp = p.front();
                if(ptmp.x == tmp.x-1 && ptmp.y == tmp.y){
                    PB = true;
                    break;
                }
                if(map[ptmp.x-1][ptmp.y] == '.')
                    p.push(position{ptmp.x-1,ptmp.y});
                if(map[ptmp.x+1][ptmp.y] == '.')
                    p.push(position{ptmp.x+1,ptmp.y});
                if(map[ptmp.x][ptmp.y-1] == '.')
                    p.push(position{ptmp.x,ptmp.y-1});
                if(map[ptmp.x][ptmp.y+1] == '.')
                    p.push(position{ptmp.x,ptmp.y+1});
                p.pop();
            }
            if(PB)
                q.push(position{tmp.x , tmp.y+1});
        }
        q.pop();
    }
    cout << ans << endl;
}
