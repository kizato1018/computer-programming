#include <iostream>
#include <cstdio>
#define INF 1e9

using namespace std;

int64_t dis[305][305];

int main() {
    int N, M;
    int64_t a, b, w, ans = INF;
    cin >> N >> M;
    for(int i = 1; i <= N; ++i) {
        fill(dis[i], dis[i]+N+1, INF);
        dis[i][i] = 0;
    }
    for(int i = 1; i <= M; ++i) {
        cin >> a >> b >> w;
        dis[a][b] = w;
    }
    // for(int i = 1; i <= N; ++i) {
    //     for(int j = 1; j <= N; ++j) {
    //         cout << dis[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    for(int k = 1; k <= N; ++k) {
        for(int i = 1; i <= N; ++i) {
            for(int j = 1; j <= N; ++j) {
                if(i == j) {
                    if(dis[i][j] == 0 && dis[i][k] + dis[k][j] < INF)
                        dis[i][j] = dis[i][k] + dis[k][j];
                    else 
                        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                    if(dis[i][j] != 0)
                        ans = min(ans, dis[i][j]);
                }
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                    
            }
        }
    }

    cout << ((ans < INF) ? ans : -1) << endl;
    // for(int i = 1; i <= N; ++i) {
    //     for(int j = 1; j <= N; ++j) {
    //         cout << dis[i][j] << " ";
    //     }
    //     cout << endl;
    // }
}