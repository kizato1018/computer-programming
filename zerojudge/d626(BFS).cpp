#include <bits/stdc++.h>

using namespace std;

class pos{
public:
	pos() {};
	pos(int _x, int _y);
	int x;
	int y;
};

pos::pos(int _x, int _y){
	x = _x;
	y = _y;
}

char canvas[102][102];
int n;
pos start;
queue<pos> q;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

void bfs(){
	pos tmp;
	q.push(start);
	while(!q.empty()){
		canvas[q.front().x][q.front().y] = '+';
		for(int i = 0; i < 4; i++){
			tmp = pos(q.front().x + dx[i], q.front().y + dy[i]);
			if(0 <= tmp.x && tmp.x < n && 0 <= tmp.y && tmp.y < n)
				if(canvas[tmp.x][tmp.y] == '-')
					q.push(tmp);
		}
		q.pop();
	}
}

void dfs(pos p){
	pos tmp;
	canvas[p.x][p.y] = '+';
	for(int i = 0; i < 4; i++){
		tmp = pos(p.x + dx[i], p.y + dy[i]);
		if(0 <= tmp.x && tmp.x < n && 0 <= tmp.y && tmp.y < n)
			if(canvas[tmp.x][tmp.y] == '-')
				dfs(tmp);
	}
}

int main(int argc, char const *argv[]){
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> canvas[i];
	}
	cin >> start.x >> start.y;
	dfs(start);
	//bfs();
	for(int i = 0; i < n; i++){
		cout << canvas[i] << endl;
	}
	return 0;
}