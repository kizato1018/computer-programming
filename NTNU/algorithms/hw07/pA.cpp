#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define INF 1e9

using namespace std;

int N, M, S, T;
int table[105][105] = {0};
int parent[105] = {0};


bool BFS() {
    bool visited[105] = {0};
    queue<int> q;
    q.push(S);
    memset(parent, 0, sizeof(parent));
    visited[S] = true;
    parent[S] = S;
    while(!q.empty()) {
        int from = q.front();
        q.pop();
        for(int i = 1; i <= N; ++i) {
            if((!visited[i]) && table[from][i] > 0) {
                q.push(i);
                parent[i] = from;
                visited[i] = true;
            }
        }
    }
    return visited[T];
}

int main() {
    
    int u, v, w;
    int max = 0;
    scanf("%d %d %d %d", &N, &M, &S, &T);
    for(int i = 0; i < M; ++i) {
        scanf("%d %d %d", &u, &v, &w);
        table[u][v] += w;
        table[v][u] += w;
    }
    while(BFS()) {
        int f = INF;
        for(int i = T; i != S; i = parent[i]) {
            f = min(f, table[parent[i]][i]);
        }
        for(int i = T; i != S; i = parent[i]) {
            table[parent[i]][i] -= f;
            table[i][parent[i]] += f;
        }
        max += f;
    }
    printf("%d\n", max);
}