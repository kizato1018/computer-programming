#include "player.h"
#include <iostream>
#include <sstream>
#include <iomanip>

int Player::Roll_Dice() const {
    int point = (rand() % 6) + 1;
    std::cout << "roll :" << point << std::endl;
    return point;
}

bool Player::Do_Act(const Action act, const int cost) {
    switch(act) {  //BUY, BUY_C, PAY, GAIN, UPGRADE, TOJAIL 
        case BUY:
            if(money_>=cost){
                money_ -= cost;
                num_unit_ += 1;
                return true;
            }
            else return false;
            break;
        case BUY_C:
            if(money_>=cost){
                money_ -= cost;
                num_unit_ += 1;
                collection_cnt_ += 1;
                return true;
            }
            else return false;
            break;
        case PAY:
        case UPGRADE:
            if(money_>=cost){
                money_ -= cost;
                return true;
            }
            else return false;
            break;
        case GAIN:
            money_ += cost;
            return true;
            break;
        case TOJAIL:
            movable_ = !movable_;
            break;
        default:
            std::cout<<"game crash\n";
            break;
    }
}

void Player::Player_Show() const {
    std::cout << "[" << id_ << "]"
              << std::setw(10) << name_ << " "
              << std::setw(7) << std::string("$") + (std::to_string(money_)) << " "
              << "with" << " " << std::setw(2) << num_unit_ << " " << "units";
    
}
void Player::Set_Location(const int loc) {
    location_ = loc;
}