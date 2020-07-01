#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <vector>
#include <fstream>
#include <string>
#include "map_unit.h"
#include "player.h"

class WorldPlayer{
public:
    Player& Get_Player(const int);
    bool Add_Player( Player * );
    void Set_Number_Player( const int number ) { number_player_ = number; }
    int Get_Number_Player() const { return number_player_; }
    int Get_Total_Number() const { return total_number_; }
    void Set_Total_Number( const int number ) { total_number_ = number; }
    
private:
    int number_player_;
    int total_number_;
    std::vector<Player *> players_;
};

class WorldMap {
public:
    bool Get_Map(std::ifstream &);
    MapUnit& Get_Unit(const int);
    int Get_Number_Unit() const { return number_map_unit_; }
    int Round_Reward() { return reward_; }
private:
    int number_map_unit_;
    int reward_ = 3000;
    std::vector<MapUnit *> units_;
};

class Game {
public:
    void Init(std::ifstream &);
    bool Is_Game_Over() { return ( game_over_ | ( world_player_.Get_Number_Player() <= 1 ) ); }
    void Bankrupt_(Player &);
    bool New_Player(const int, const std::string);
    Condition Move(const int);
    void Show_Info(const int);
    void Show_Map();
    void Show_A_Unit( const int );
    void Travel( const int , Condition);
    void Show_Event(const Condition, const Player &, const MapUnit &);
    void Execute_Event( const Condition, Player &, MapUnit & );
    int Get_Number_Player() const { return world_player_.Get_Number_Player(); }
    int Get_Total_Player() const { return world_player_.Get_Total_Number(); }
    int Next_Player(const int);
private:
    void Game_Over() { game_over_ = true; }
    bool game_over_ = false;
    WorldPlayer world_player_;
    WorldMap world_map_;
};

#endif // GAME_H_INCLUDEDd;