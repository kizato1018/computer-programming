#include <iostream>
#include "maze.h"
#include "robot.h"

using namespace std;

int main() {
    int W, H;
    Pos p;
    int64_t n;
    Robot robot;
    cin >> W >> H;
    Maze M(W, H);
    M.SetMap();
    cin >> n;
    robot.Setup(M);
    M.PrintMap();
    p = robot.Go(n, M);
    cout << "(" << p.x << ", " << p.y << ")" << endl;

}
