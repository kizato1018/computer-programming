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

Robot Maze::GetPlayer() {
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if(Map[i][j] == 'O') {
                for(int k = 0; k < 4; k++) {

                }
            }
        }
    }
}

void Maze::PrintMap() {
    for(int i = 0; i < h; i++) {
        cout << Map[i] << endl;
    }
}
