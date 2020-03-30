#include "robot.h"

void Robot::Setup(const Maze &m) {
	 for(int i = 0; i < m.GetHeight(); i++) {
        for(int j = 0; j < m.GetWidth(); j++) {
            if(m.GetPostion(Pos{.x = j, .y = i}) == 'O') {
                SetPos(Pos{.x = j, .y = i});
                for(int k = 0; k < 4; k++) {
                    if(m.GetPostion(Pos{.x = j, .y = i} + dir[k]) == '#' &&
                       m.GetPostion(Pos{.x = j, .y = i} + dir[k+1]) != '#')
                       SetDirection(k+1);
                }
            }
        }
    }
}

Pos Robot::Go(int64_t n, const Maze &m) {
	int cnt = 0;
	while(n--) {
		if(m.GetPostion(pos+dir[direct]) == '.') {
			pos = pos + dir[direct];
			cnt++;
		}
		else if(m.GetPostion(pos+dir[direct]) == '#') {
			direct = (direct + 1) % 4;
			n++;
		}
		else {
			pos = pos + dir[direct];
            cnt++;
			n %= cnt;
		}
	}
	return pos;
}
