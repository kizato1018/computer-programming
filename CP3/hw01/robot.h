#ifndef __ROBOT_H__
#define __ROBOT_H__
#include <cstdint>

struct Pos{
	int x;
	int y;
	Pos operator+(Pos tar) { return Pos{.x = x + tar.x, .y = y + tar.y}; }
	Pos operator-(Pos tar) { return Pos{.x = x - tar.x, .y = y - tar.y}; }
	void operator=(Pos tar) { x = tar.x, y = tar.y; }
};
// c.x = a.x + b.x
// c.y = a.y + b.y
// c = a + b

class Robot{
public:
	Robot() { pos = Pos{.x = 0, .y = 0}; direct = Pos{.x = 0, .y = 0}; }
	void SetPos(Pos p) { pos = p; }
	void SetDirection(Pos d) { direct = d; }
	void Go(int64_t n);

private:
	Pos pos;
	Pos direct;
};

#endif
