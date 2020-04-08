#include <iostream>
#include "maze.h"
#include "robot.h"

using namespace std;

int main() {
    int W, H;
<<<<<<< HEAD
    Robot robot;
    cin >> W >> H;
    Maze M(W, H);
    M.GetMap();
    robot = M.GetRobot();
    M.PrintMap();
=======
    Pos p;
    int64_t n;
    Robot robot;
    cin >> W >> H >> n;
    Maze M(W, H);
    M.SetMap();
    robot.Setup(M);
    p = robot.Go(n, M);
    cout << p.x << " " << p.y << endl;
>>>>>>> refs/remotes/origin/master

}
