#ifndef __MAZE_H__
#define __MAZE_H__
#include <vector>
#include <iostream>


class Maze{
public:
    Maze(int W, int H);
    void GetMap();
    Robot GetRobot();
    void PrintMap();
private:
    int w, h;
    std::vector<std::string> Map;
};

#endif
