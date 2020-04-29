#include <iostream>
#include "maze.h"
#include "robot.h"

using namespace std;

int main() {
    int W = 0, H = 0;
    Pos p = Pos{.x = 0, .y = 0};
    int64_t n = 0;
    Robot robot;
    Maze M;
    
    cin >> W >> H >> n;
    M.SetMap(W, H);
    robot.Setup(M);
    p = robot.Go(n, M);
    cout << p.x << " " << p.y << endl;

}
