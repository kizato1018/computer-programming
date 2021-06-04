#ifndef __MAZE_H__
#define __MAZE_H__
#include <vector>
#include <iostream>

struct Pos{
	int x;
	int y;
	Pos operator+(const Pos tar) const { return Pos{.x = x + tar.x, .y = y + tar.y}; }
	Pos operator-(const Pos tar) const { return Pos{.x = x - tar.x, .y = y - tar.y}; }
	void operator=(const Pos tar) { x = tar.x, y = tar.y; }
};

class Maze{
public:
    Maze() { w = 0; h = 0; }
    void SetMap(const int W, const int H);
    char GetPostion(const Pos p) const { return Map[p.y][p.x]; }
    int GetWidth() const { return w; }
    int GetHeight() const { return h; }
    void PrintMap() const;
private:
    int w, h;
    std::vector<std::string> Map;
};

#endif
