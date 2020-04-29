#ifndef __ROBOT_H__
#define __ROBOT_H__
#include "maze.h"

class Robot{
public:
	Robot() { pos = Pos{.x = 0, .y = 0}; direct = 0; }
	void Setup(const Maze &m);
	Pos Go(const int64_t n, const Maze &m);

private:
	void SetPos(const Pos p) { pos = p; }
	void SetDirection(const int d) { direct = d; }
	Pos pos;
	int direct;
};

#endif
