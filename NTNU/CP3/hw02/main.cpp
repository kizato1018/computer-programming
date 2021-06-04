#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

#define For(i, a, b) for(int i = a; i < b; i++) 

using namespace std;

struct Position{    /* x, y 座標 */
    int x;
    int y;
    Position operator+(Position tar){
        return Position{.x = x + tar.x, .y = y + tar.y};
    }
	Position operator-(Position tar){
        return Position{.x = x - tar.x, .y = y - tar.y};
    }
    double operator/(Position tar){
        return max((double)x / tar.x, (double)y / tar.y);
    }
    bool operator==(const Position tar) { return x == tar.x && y == tar.y ; }
    friend ostream &operator<<(ostream &s, Position tar);
};

ostream &operator<<(ostream &s, Position tar){
    s << tar.x << " " << tar.y << endl;
    return s;
}

int dis(Position p1,Position p2){                               /* 兩點間距離 */
    return sqrt( pow((p1.x-p2.x),2)+pow((p1.x-p2.x),2) );
}

int dis_point2line(Position p,int a,int b,int c){               /* 點到直線距離 */
	return (abs((a*p.x)+(b*p.y)+c)/sqrt(a*a+b*b));
}

class Zone{     /* 戰區 */
    public:
        Zone(){};
        Zone(Position p, int id = -1) { _pos = p; _ID = id; }
        Zone(int x, int y, int id = -1) { _pos = Position{.x = x, .y = y}; _ID = id; }
        /* for user */
		Position pos() const { return _pos; }                   /* 戰區座標 */
		int droneNum(int id) const { return _droneNum[id]; }    /* 戰區中各隊無人機數量 */
		int maxDroneNum() const { return _maxDroneNum; }        /* 戰區中無人機數量最大值 */
		int belong() const { return _belong; }                  /* 目前佔領此戰區的隊伍 */
        int ID() const { return  _ID; }                         /* 戰區ID */
    private:
        Position _pos;
        int _droneNum[4];
        int _maxDroneNum;
        int _belong;
        int _ID;
        void _newRound() { for(int i = 0; i < 4; i++) _droneNum[i] = 0; }
        void _countDrone(int id) { _droneNum[id]++; _maxDroneNum = max(_maxDroneNum, _droneNum[id]); }

    friend class Game;
    friend class Player;
    friend class Drone;
};

bool ZoneCmp(Zone *a, Zone *b) { return a->maxDroneNum() > b->maxDroneNum(); }


class Drone{    /* 無人機 */
    public:
        Drone(){};
        Drone(int x, int y, int id) { _nowPos = Position{.x = x, .y = y}; _ID = id; }
        Drone(Position p, int  id) { _nowPos = p; _ID = id; }
        /*for user */
        Position nowPos() const { return _nowPos; }             /* 現在位置 */
        Position lastPos() const { return _lastPos; }           /* 前一個位置 */
        int ID() const { return _ID; }                          /* 無人機ID */
        int belong() const { return _belong; }                  /* 屬於哪位玩家的 */
        int inZone() const { return _inZone; }                  /* 在哪個戰區 */
        Position targetPos() const { return _targetPos; }       /* 目標位置 */
        bool isBusy() const { return _isBusy; }                 /* 他很忙ㄇ?1:0 */
        Zone near_zone() const { return _near_zone; }           /* 最近的戰區是哪個 */
    private:
        Position _nowPos;
        Position _lastPos;
        int _ID;
        int _belong;
        int _inZone;
        Position _targetPos;
        bool _isBusy;
        Zone _near_zone;
        void _setPos(Position pos);
        void _settargetPos(Position );
        void _getNear_zone(vector<Zone> );
		void _preditTargetPos(const vector<Zone> );
        int _tmpDis;
    friend class Game;
    friend class Player;
    friend bool DroneCmp(Drone *a, Drone *b);
};

bool DroneCmp(Drone *a, Drone *b) { return a->_tmpDis < a->_tmpDis; }

void Drone::_settargetPos(Position pos){
    _targetPos = pos;
    _isBusy = 1;
}


void Drone::_setPos(Position pos){
    _lastPos = _nowPos;
    _nowPos = pos;
}

void Drone::_getNear_zone(vector<Zone> zone){
    int _min = 1e9;
    Zone minZone;
    for( auto i : zone ){
        int d = dis(_nowPos, i.pos());
        if(d <= 100){
            _inZone = i.ID();
            zone[_inZone]._countDrone(_belong);
        }
        if( _min > d){
            _min = d;
            minZone = i;
        }
    }
    _near_zone = minZone;
    /* cerr << "drone ID:" << _ID << " near_zone:" << _near_zone.ID() << " " << _near_zone.getPos() << endl; */
}

void Drone::_preditTargetPos(const vector<Zone> zone){
    int minDis=1e9;
	Zone closetZone;
	_targetPos=_nowPos-_lastPos;
	if(_targetPos == Position{0,0}){ 
		_targetPos = Position{-1,-1};
		_isBusy=0;
		return;
	}
	_isBusy=1;
    
    for(auto i : zone){
		if(dis_point2line(i._pos,_targetPos.y,-_targetPos.x,-(_targetPos.y*_nowPos.x-_targetPos.x*_nowPos.y))<=100){
			if(dis(i._pos,_nowPos)<minDis){
				minDis=dis(i._pos,_nowPos);
				closetZone=i;
			}
		}
    }
	if(minDis!=1e9) _targetPos=closetZone._pos;
}

class Player{   /* 玩家 */
    public:
        Player(){};
        vector<Drone> drone;                                    /* 這個玩家的無人機 */
        vector<Drone*> freedrone;                               /* 不忙的無人機 */
        vector<Drone*> buzydrone;                               /* 很忙的無人機 */
        vector<Zone*> myzone;                                   /* 屬於我的戰區(從maxDroneNum最小到最大) */
        vector<Zone*> otherzone;                                /* 別人的戰區(從maxDroneNum最小到最大) */
        int FreeDroneNumber;                                    /* 有幾台無人機有空 */
        int DroneNumber;                                        /* 我有幾台無人機 */
        void setMyDrone(int , Position );                       /* 設定我的無人機要去哪(無人機ID,要去的位置) */
        vector<Drone*> DroneInZone(int );                       /* 哪些無人機在那個Zone裡面(Zone ID) */
        vector<Drone*> nearDrone(Position, vector<Drone>);      /* 對某個點對所有無人機從近到遠排序 */
        vector<Drone*> nearDrone(Position, vector<Drone*>);     /* 對某個點對所有無人機從近到遠排序 */
    private:
        int _ID;
        void _setDrone(const int , const vector<Zone> );
        void _updateZone(const int , const vector<Zone> );
		void _setDrone_onlyEnemy(const int , const vector<Zone>);
        //bool cmp(Drone *a, Drone *b) { return dis(a->_nowPos , pos) < dis(b->_nowPos , pos); }
    friend class Game;
};

void Player::setMyDrone(int ID , Position pos){
    drone[ID]._settargetPos(pos);
    for(int i = 0; i < freedrone.size(); i++) {
        if(freedrone[i]->ID() == ID) {
            buzydrone.push_back(freedrone[i]);
            freedrone.erase(freedrone.begin()+i);
        }
    }
    FreeDroneNumber--;
}

void Player::_setDrone(const int Num, const vector<Zone> zone){
    for(int id = 0; id < Num; id++){
        Position p;
        cin>>p.x>>p.y; cin.ignore();
        drone[id]._setPos(p);
        drone[id]._getNear_zone(zone);
        freedrone.push_back(&(drone[id]));
        drone[id]._isBusy = 0;
        /* cerr << drone[id]._nowPos << endl; */
    }
    FreeDroneNumber = DroneNumber;
}

void Player::_updateZone(const int Num, vector<Zone> zone){
    myzone.clear();
    otherzone.clear();
    for(int j = 0; j < Num; j++){
        if(zone[j].belong() == _ID)
            myzone.push_back(&(zone[j]));
        else 
            otherzone.push_back(&(zone[j]));
    }
    sort(myzone.begin(), myzone.end(), ZoneCmp);
    sort(otherzone.begin(), otherzone.end(), ZoneCmp);
}

void Player::_setDrone_onlyEnemy(const int Num, const vector<Zone> zone){
    for(int id = 0; id < Num; id++){
        drone[id]._preditTargetPos(zone);
    }
}

vector<Drone*> Player::DroneInZone(int ZoneID){
    vector<Drone*> r;
    for(int i = 0; i < drone.size(); i++) {
        if(drone[i]._inZone == ZoneID)
            r.push_back(&(drone[i]));
    }
    return r;
}

vector<Drone*> Player::nearDrone(Position pos, vector<Drone> _drone){
    vector<Drone*> r;
    for(int i = 0; i < _drone.size(); i++) {
        _drone[i]._tmpDis  = dis(_drone[i]._nowPos, pos);
        r.push_back(&(_drone[i]));
    }
    
    sort(r.begin(), r.end(), DroneCmp);
    return r;
}

vector<Drone*> Player::nearDrone(Position pos, vector<Drone*> _drone){
    vector<Drone*> r;
    for(int i = 0; i < _drone.size(); i++) {
        _drone[i]->_tmpDis  = dis(_drone[i]->_nowPos, pos);
        r.push_back(_drone[i]);
    }
    sort(r.begin(), r.end(), DroneCmp);
    return r;
}

class Game{ /* 遊戲主體 */
    public:
        Game(){};
        void Start(vector<Player> &player, vector<Zone> &zone);                 /* 開始的預處理 */
        void Round(vector<Player> &player, vector<Zone> &zone);                 /* 每一次讀入的資料處理 */
        void Run(vector<Player> &player);                                       /* 輸出這次的結果 */
        void Debug(vector<Player> const &player, vector<Zone> const &zone);     /* Debug */
        int playerID() { return _playerID; }                                    /* 我的ID */
        int droneNum() const { return _droneNum;}                               /* 每個人有幾台無人機 */
    private:
        int _playerNum;
        int _playerID;
        int _droneNum;
        int _zoneNum;

};

void Game::Start(vector<Player> &player, vector<Zone> &zone){
	cin>>_playerNum>>_playerID>>_droneNum>>_zoneNum;
	for(int i = 0; i < _zoneNum; i++){
        int x, y;
        cin >> x >> y; cin.ignore();
        Zone z(x, y, i);
        zone.push_back(z);
	}
    for(int i = 0; i < _playerNum; i++){
        Player ply;
        for(int j = 0; j < _droneNum; j++){
            Drone d(-1,-1,j);
            d._belong = i;
            ply.drone.push_back(d);
        }
        ply.DroneNumber = _droneNum;
        player.push_back(ply);

    }
}

void Game::Round(vector<Player> &player, vector<Zone> &zone){
    for(int i = 0; i < _zoneNum; i++){
        int TID;
        cin>>TID; cin.ignore();
        zone[i]._belong = TID;
        zone[i]._newRound();
    }
    for(int i = 0; i < _playerNum; i++){
        player[i]._setDrone(_droneNum, zone);
        player[i]._updateZone(_zoneNum, zone);
        if(i != _playerID){
            player[i]._setDrone_onlyEnemy(_droneNum, zone);
        }
    }
    
}

void Game::Run(vector<Player> &player){
    for(auto i : player[_playerID].drone){
        cout << i._targetPos;
    }
}

void Game::Debug(vector<Player> const &player, vector<Zone> const &zone){
    cerr << "ID" << _playerID << endl;
    cerr << "Drone num" << _droneNum << endl;
    for(auto i : player[_playerID].drone){
        cerr << i._targetPos;
    }
}

int main(){
    /* 宣告區域 */
    Game game;
    vector<Player> player;
    vector<Zone> zone;

    /* 遊戲初始化 */
    game.Start(player, zone);
    const int ID = game.playerID();                     /* 建議搭配食用 */
    const vector<Drone> &Mydrone = player[ID].drone;    /* 建議搭配食用 */
    Player &My = player[ID];			                /* 建議搭配食用 */
    /* 遊戲迴圈 */
    while(1){
        game.Round(player, zone);                       /* 每局開始 */
        
		for(auto i : zone){
			if(i.belong() == ID){
				int n = i.maxDroneNum();
				while(n--){
					for(auto j : My.DroneInZone(i.ID())){
						My.setMyDrone(j->ID(), i.pos());
					}
				}
			}
		}
		
		for(auto i:zone){
			if(i.belong() == -1){
				vector<Drone*> near = My.nearDrone(i.pos(), My.freedrone);
				if(!near.empty()) My.setMyDrone(near[0]->ID(), i.pos());
			}
		}
		
		for(auto i : My.otherzone){
			if(My.FreeDroneNumber > i->maxDroneNum()){
				int n=i->maxDroneNum();
				while(n--){
					for(auto j : My.nearDrone(i->pos(), My.freedrone)){
						My.setMyDrone(j->ID(), i->pos());
					}
				}
			}
		}
	
		for(auto i : My.freedrone){
			My.setMyDrone(i->ID(), i->near_zone().pos());
		}

        game.Run(player);                       /* 執行指令 */
    }
    return 0;
}
