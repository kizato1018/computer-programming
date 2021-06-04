#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge{
    int v;
    int w;
};

int Begin = 0, End = 0;
vector<Edge> vertex[3010];
bool visited[3010];

int DFS(int n) {
    if(n == End) {
        return 100000;
    }
    else if(visited[n]) return -1;
    visited[n] = true;
    int a;
    for(int i = 0; i < vertex[n].size(); ++i) {
        a = DFS(vertex[n][i].v);
        if(a > 0)
            return min(vertex[n][i].w, a);
    }
    return -1;
}

int main() {
    int32_t N;
    int32_t u, v, w;
    cin >> N;
    for(int32_t i = 1; i < N; ++i) {
        cin >> u >> v >> w;
        vertex[u].push_back(Edge{.v = v, .w = w});
        vertex[v].push_back(Edge{.v = u, .w = w});
    }
    cin >> Begin >> End;
    cout << DFS(Begin) << endl;
}
