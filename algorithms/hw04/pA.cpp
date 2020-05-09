#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> vertex[100010];
bool check[100010] = {0};

bool cmp(int a, int b) {return a>b;}

bool DFS(int N) {
    printf("%d ", N);
    check[N] = true;
    sort(vertex[N].begin(), vertex[N].end(), cmp);
    // for(int i = 0; i < vertex[N].size(); ++i) {
    for(auto i : vertex[N]) {
        if (check[i])
            continue;
        else if(DFS(i))
            return true;
    }
    return false;
}

int main() {
    int N;
    int u, v;
    scanf("%d", &N);
    for(int i = 0; i < N-1; ++i) {
        scanf("%d %d", &u, &v);
        vertex[u].push_back(v);
        vertex[v].push_back(u);
    }
    DFS(N);
}