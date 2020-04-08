#ifndef __MAZE_H__
#define __MAZE_H__
#include <vector>
#include <iostream>

struct Pos{
	int x;
	int y;
	Pos operator+(Pos tar) { return Pos{.x = x + tar.x, .y = y + tar.y}; }
	Pos operator-(Pos tar) { return Pos{.x = x - tar.x, .y = y - tar.y}; }
	void operator=(Pos tar) { x = tar.x, y = tar.y; }
};

class Maze{
public:
<<<<<<< HEAD
    Maze(int W, int H);
    void GetMap();
    Robot GetRobot();
    void PrintMap();
=======
    Maze(const int W, const int H);
    void SetMap();
    char GetPostion(Pos p) const { return Map[p.y][p.x]; };
    int GetWidth() const { return w; }
    int GetHeight() const { return h; }
    void PrintMap() const;
>>>>>>> refs/remotes/origin/master
private:
    int w, h;
    std::vector<std::string> Map;
};

#endif
