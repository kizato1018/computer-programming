#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>

enum Action {BUY, BUY_C, PAY, GAIN, UPGRADE, TOJAIL };

class Player{
public:
    Player(const int id, const std::string name) 
        : id_(id), name_(name), location_(0), money_(start_money_), num_unit_(0), movable_(true), collection_cnt_(0), bankrupt_(false) {}
    int Roll_Dice() const;
    bool Do_Act(const Action, const int cost = 0); 
    void Player_Show() const;

    void Set_Location(const int);
    int Get_Money() const { return money_; }
    bool Is_Bankrupt() const { return bankrupt_; }
    void Bankrupt() { bankrupt_ = true; }

    int Get_Id() const { return id_; }
    int Get_Collection_Cnt() const { return collection_cnt_; }
    std::string Get_Player_Name() const { return name_; }
    int Get_Location() const { return location_; }
    bool Is_Movable() const { return movable_; }
    friend bool operator==(const Player &lhs, const Player &rhs) { return lhs.id_ == rhs.id_; }
private:
    static constexpr int start_money_ = 30000;
    int id_;
    std::string name_;
    int location_;
    int money_;
    int num_unit_;
    bool movable_;
    int collection_cnt_;
    bool bankrupt_;
};

#endif