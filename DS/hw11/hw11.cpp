#include <bits/stdc++.h>
#define INF 1e9

using namespace std;

struct Node{
    int id;
    int dis;
};
struct Edge{
    int a;
    int b;
    int w;
    int belong;
};

bool operator<(Node a, Node b) {return a.dis > b.dis;}
int V, E, C, D;
int city_belong[25] = {0};
Edge edge[2005] = {0};
int path[105] = {0};

void ShowPath(int v) {
    if(path[v] == v) {
        cout << v << " ";
        return;
    }
    ShowPath(path[v]);
    cout << v << " ";
}

int dijkstra(int start, int end) {
    int d[105];
    bool visited[105] = {0};
    int cost[105][105] = {0};
    for(int i = 1; i <= V; ++i) {
        d[i] = INF;
        path[i] = 0;
        visited[i] = false;
    }
    for(int i = 1; i <= V; ++i) 
        for(int j = 1; j <= V; ++j) 
            cost[i][j] = (i == j) ? 0 : INF;
    for(int i = 0; i < E; ++i) {
        int w = (city_belong[start] == edge[i].belong) ? edge[i].w : edge[i].w * D;
        if(cost[edge[i].a][edge[i].b] > w) {
            cost[edge[i].a][edge[i].b] = w;
            cost[edge[i].b][edge[i].a] = w;
        }
    }
    d[start] = 0;
    path[start] = start;
    priority_queue<Node> pq;
    pq.push(Node{start, 0});

    for(int i = 0; i < V; ++i) {
        int v = -1;
        while(!pq.empty()){
            v = pq.top().id;
            if(!visited[v]) break;
            pq.pop();
        }
        if(v == -1) break;
        visited[v] = true;
        for(int j = 1; j <= V; ++j) {
            if(!visited[j] && d[v] + cost[v][j] < d[j]) {
                d[j] = d[v] + cost[v][j];
                path[j] = v;
                pq.push(Node{j, d[j]});
            }
        }
    }
    ShowPath(end);
    cout << "\n";
    return d[end];

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N;
    int x, y;
    int sum = 0;
    cin >> V >> E >> C;
    for(int i = 1; i <= V; ++i)
        cin >> city_belong[i];
    for(int k = 0; k < E; ++k) {
        int i, j, w, belong;
        cin >> edge[k].a >> edge[k].b >> edge[k].w >> edge[k].belong;
    }
    cin >> D;
    cin >> N;
    cin >> x;
    for(int i = 1; i < N; ++i) {
        cin >> y;
        sum += dijkstra(x, y);
        x = y;
    }
    cout << sum;
}

/*
7 10 2
1 1 2 2 1 2 2
1 2 5 1
1 3 2 2
2 5 2 1
2 6 8 2
3 4 1 2
3 5 2 1
4 5 1 2
4 7 4 2
5 7 8 1
6 7 2 2
2
2
1 5
*/

/*
5 4 1
1 1 1 1 1
1 2 1 1
1 3 5 1
2 4 1 1
3 5 5 1
2
2
1 5

*/