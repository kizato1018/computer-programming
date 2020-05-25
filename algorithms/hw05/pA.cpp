#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge{
    int v;
    int w;
};

int begin = 0, end = 0;
vector<Edge> vertex[3010];
int weight[3010][3010];
bool visited[3010];

int DFS(int n) {
    if(n == end) {
        return 1;
    }
    else if(visited[n]) return 0;
    visited[n] = true;
    int a, Min = 100000;
    for(int i = 1; i <= N; ++i) {
        if(weight[n][i])
            if(a = DFS(i))
                return min(weight[n][i], a);
        else    
            continue;
        if(a != 0) 
            return min(Min, a);
    }
}

int main() {
    int32_t N;
    int32_t u, v, w;
    cin >> N;
    for(int32_t i = 1; i < N; ++i) {
        // S[i] = i;
        // cin >> e[i].u >> e[i].v >> e[i].w;
        cin >> u >> v >> w;
        vertex[u].push_back(v);
        vertex[v].push_back(u);
    }
    cin >> begin >> end;
    for(int32_t i = 1; i <= N; ++i) {
        pq.push(vertex[begin])
        sort(vertex[i].begin(), vertex[i].end(), [](Edge a, Edge b){return a.w > b.w;});
    }
    
}