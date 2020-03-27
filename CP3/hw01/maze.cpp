#include <cstdlib>
#include "robot.h"
#include "maze.h"

using namespace std;


Maze::Maze(int W, int H) {
    w = W;
    h = H;
}

void Maze::GetMap() {
    for(int i = 0; i < h; i++) {
        string s;
        cin >> s;
        Map.push_back(s);
    }
}

Robot Maze::GetRobot() {
    Robot robot;
    Pos dir[4] = {{.x = -1, .y = 0},
                  {.x = 0, .y = -1},
                  {.x = 1, .y = 0},
                  {.x = 0, .y = 1}};
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if(Map[i][j] == 'O') {
                robot.SetPos(Pos{.x = j, .y = i});
                for(int k = 0; k < 4; k++) {
                    if(Map[i+dir[k].y][j+dir[k].x] == '#' &&
                       Map[i+dir[(k+1)%4].y][j+dir[(k+1)%4].x] != '#')
                       robot.SetDirection(dir[k+1]);
                }
            }
        }
    }
    return robot;
}

void Maze::PrintMap() {
    for(int i = 0; i < h; i++) {
        cout << Map[i] << endl;
    }
}
