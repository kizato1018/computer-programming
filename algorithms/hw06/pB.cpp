#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#define INF 1e9

using namespace std;



struct Vertex{

    int64_t dis;
    bool visited;
}v[100010];


int main() {
    int N, M;
    int path[4];
    int64_t a, b, w, Min, ans = 0;
    vector<Edge>::iterator it;
    scanf("%d %d", &N, &M);
    for(int i = 0; i < 4; ++i)
        scanf("%d", &path[i]);
    for(int i = 0; i < M; ++i) {
        scanf("%ld %ld %ld", &a, &b, &w);
        Map[a].push_back(Edge{.v = b, .w = w});
        Map[b].push_back(Edge{.v = a, .w = w});
    }
    for(int j = 1; j <= N; ++j) {
        v[j].dis = INF;
        v[j].visited = false;
    }
    for(int i = 0; i < N; ++i) {

        v[path[0]].dis = 0;
        a = 0;
        Min = INF;
        for(int j = 1; j <= N; ++j ) {
            if(!v[j].visited && v[j].dis < Min) {
                a = j;
                Min = v[j].dis;
            }
        }
        if(a == 0) break;
        // printf("a = %d\n", a);
        v[a].visited = true;
        for(int j = 1; j <= N; ++j) {
            if(!v[j].visited) {
                if((it = find_if(Map[j].begin(), Map[j].end(), [a](Edge e){return e.v == a;})) != Map[j].end())
                    v[j].dis = min(v[j].dis, v[a].dis + it->w);
            }
        }
        // for(int j = 1; j <= N; ++j) 
            // printf("%d: %d\n", j, v[j].dis);
    }
    ans += v[path[1]].dis + v[path[3]].dis;
    for(int j = 1; j <= N; ++j) {
        v[j].dis = INF;
        v[j].visited = false;
    }
    for(int i = 0; i < N; ++i) {

        v[path[2]].dis = 0;
        a = 0;
        Min = INF;
        for(int j = 1; j <= N; ++j ) {
            if(!v[j].visited && v[j].dis < Min) {
                a = j;
                Min = v[j].dis;
            }
        }
        if(a == 0) break;
        v[a].visited = true;
        for(int j = 1; j <= N; ++j) {
            if(!v[j].visited)
                if((it = find_if(Map[j].begin(), Map[j].end(), [a](Edge e){return e.v == a;})) != Map[j].end())
                    v[j].dis = min(v[j].dis, v[a].dis + it->w);
        }
    }
    ans += v[path[1]].dis + v[path[3]].dis;
    cout << ans << endl;
}