#ifndef ROBOT_H
#define ROBOT_H

struct Pos{
	int x;
	int y;
};

class Robot{
public:
	Robot(Maze M);
	Pos getpos() {return pos;}
	void Go();
private:
	Pos pos;
	int8_t direct;
}

#endif
