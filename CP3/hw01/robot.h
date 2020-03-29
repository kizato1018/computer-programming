#ifndef __ROBOT_H__
#define __ROBOT_H__
#include "maze.h"
// c.x = a.x + b.x
// c.y = a.y + b.y
// c = a + b

class Robot{
public:
	Robot() { pos = Pos{.x = 0, .y = 0}; direct = 0; }
	void Setup(const Maze &m);
	Pos Go(int64_t n, const Maze &m);

private:
	void SetPos(Pos p) { pos = p; }
	void SetDirection(int d) { direct = d; }
	Pos pos;
	int direct;
	Pos dir[4] = {{.x = -1, .y = 0},
				  {.x = 0, .y = -1},
				  {.x = 1, .y = 0},
				 {.x = 0, .y = 1}};
};

#endif
