#include <iostream>
#include <vector>
#include "robot.h"
#include "maze.h"

using namespace std;


int main() {
    int W, H;
    cin >> W >> H;
    Maze M(W, H);
    M.GetMap();
    M.PrintMap();

}
