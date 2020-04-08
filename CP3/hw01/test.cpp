#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;


struct Pos{
	int x;
	int y;
	Pos operator+(Pos tar) { return Pos{.x = x + tar.x, .y = y + tar.y}; }
	Pos operator-(Pos tar) { return Pos{.x = x - tar.x, .y = y - tar.y}; }
	void operator=(Pos tar) { x = tar.x, y = tar.y; }
};

class Maze{
public:
    Maze(const int W, const int H);
    void SetMap();
    // Robot GetRobot();
    char GetPostion(Pos p) const { return Map[p.y][p.x]; };
    int GetWidth() const { return w; }
    int GetHeight() const { return h; }
    void PrintMap() const;
private:
    int w, h;
    vector<string> Map;
};

class Robot{
public:
	Robot() { pos = Pos{.x = 0, .y = 0}; direct = 0; }
	void Setup(const Maze &m);
	Pos Go(int64_t n, const Maze &m);

private:
	void SetPos(Pos p) { pos = p; }
	void SetDirection(int d) { direct = d; }
	Pos pos;
	int direct;
	Pos dir[4] = {{.x = -1, .y = 0},
				  {.x = 0, .y = -1},
				  {.x = 1, .y = 0},
				 {.x = 0, .y = 1}};
};

Maze::Maze(const int W, const int H) {
    w = W;
    h = H;
}

void Maze::SetMap() {
    for(int i = 0; i < h; i++) {
        string s;
        cin >> s;
        Map.push_back(s);
    }
}

void Maze::PrintMap() const{
    for(int i = 0; i < h; i++) {
        cout << Map[i] << endl;
    }
}

void Robot::Setup(const Maze &m) {
	for(int i = 0; i < m.GetHeight(); i++) {
        for(int j = 0; j < m.GetWidth(); j++) {
            if(m.GetPostion(Pos{.x = j, .y = i}) == 'O') {
                SetPos(Pos{.x = j, .y = i});
                for(int k = 0; k < 4; k++) {
                    if(m.GetPostion(Pos{.x = j, .y = i} + dir[k]) == '#' &&
                       m.GetPostion(Pos{.x = j, .y = i} + dir[k+1]) != '#')
                       SetDirection(k+1);
                }
            }
        }
    }
    //printf("(%d, %d), %d\n", pos.x, pos.y, direct);
}

Pos Robot::Go(int64_t n, const Maze &m) {
	int cnt = 0;
	while(n--) {
		if(m.GetPostion(pos+dir[direct]) == '.') {
			pos = pos + dir[direct];
			cnt++;
		}
		else if(m.GetPostion(pos+dir[direct]) == '#') {
			direct = (direct + 1) % 4;
			n++;
		}
		else {
			//n--;
            cnt++;
			pos = pos + dir[direct];
			n %= cnt;
		}
        //printf("n=%ld, (%d, %d), %d\n", n, pos.x, pos.y, direct);
	}
	return pos;
}

int main() {
    int W, H;
    Pos p;
    int64_t n;
    Robot robot;
    cin >> W >> H >> n;
    Maze M(W, H);
    M.SetMap();
    
    robot.Setup(M);
    //M.PrintMap();
    p = robot.Go(n, M);
    cout << p.x << " " << p.y << endl;

}
