#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#define INF 1e13

using namespace std;

struct Edge {
    int64_t v;
    int64_t w;
};
vector<Edge> Map[100010];

struct Vertex {
    int id;
    int64_t dis;
    bool visited;
}v[100010];

int N;


bool operator > (Vertex a, Vertex b) { return a.dis > b.dis; }

int64_t dijkstra(int start, int end1, int end2) {
    int a = 0;
    priority_queue<Vertex, vector<Vertex>, greater<Vertex> > pq;
    for(int i = 1; i <= N; ++i) {
        v[i].id = i;
        v[i].dis = INF;
        v[i].visited = false;
    }
    v[start].dis = 0;
    pq.push(v[start]); 

    while(1) {
        a = 0;  
        while(!pq.empty()) {
            if(!pq.top().visited) {
                a = pq.top().id;   
                pq.pop();
                break;
            }
            else 
                pq.pop();     
        }

        if(a == 0) break;
        v[a].visited = true;

        for(auto j : Map[a]) {
            if(!v[j.v].visited && v[a].dis + j.w < v[j.v].dis) {
                v[j.v].dis = v[a].dis + j.w;
                pq.push(v[j.v]);
            }
        }
        // for(int j = 1; j <= N; ++j) 
        //     printf("%d: %ld\n", j, v[j].dis);
    }
    return v[end1].dis + v[end2].dis;
}

int main() {
    int M;
    int path[4];
    int64_t a, b, w, ans = 0;
    
    scanf("%d %d", &N, &M);
    for(int i = 0; i < 4; ++i)
        scanf("%d", &path[i]);
    for(int i = 0; i < M; ++i) {
        scanf("%ld %ld %ld", &a, &b, &w);
        Map[a].push_back(Edge{.v = b, .w = w});
        Map[b].push_back(Edge{.v = a, .w = w});
    }
    ans = dijkstra(path[0], path[1], path[3]) + dijkstra(path[2], path[1], path[3]);
 
    cout << ans << endl;
}

// 100000 4
// 1 2 3 100000
// 1 2 3 
// 2 3 4
// 3 100000 100
// 100000 1 20