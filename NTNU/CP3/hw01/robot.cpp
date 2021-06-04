#include "robot.h"

constexpr Pos dir[4] = {{.x = -1, .y = 0},
						{.x = 0, .y = -1},
						{.x = 1, .y = 0},
						{.x = 0, .y = 1}};

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

Pos Robot::Go(const int64_t n, const Maze &m) {
	int64_t step = n;
	int32_t cnt = 0;
	while(step--) {
		if(m.GetPostion(pos+dir[direct]) == '.') {
			pos = pos + dir[direct];
			cnt++;
		}
		else if(m.GetPostion(pos+dir[direct]) == '#') {
			direct = (direct + 1) % 4;
			step++;
		}
		else {
			pos = pos + dir[direct];
            cnt++;
			step %= cnt;
		}
	}
	return pos;
}
