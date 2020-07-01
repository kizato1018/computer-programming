#include <iomanip>
#include "map_unit.h"

MapUnit::MapUnit(int id, std::string name) : id_(id), name_(name), who_is_here_(0) {
    if(id == 0)
        who_is_here_ = ~0;
}

Condition MapUnit::Travel(int player) {// 回傳動作。
    who_is_here_ |= (1 << player);
}
void MapUnit::Leave(int player) {
    who_is_here_ &= ~(1 << player);
}
void MapUnit::Map_Show(int num, int cont) const { // format: [id] name 需要總玩家數 
    std::cout<<"=";
    for(int i=0;i<num;++i){
        if(who_is_here_&(1<<i)){
            std::cout<<i;
        }
        else{
            std::cout<<" ";
        }
    }
    std::cout<<"= ["<<std::setw(2)<<id_<<"] ";
    std::cout<<std::setw(10)<<name_<<" ";
}
void MapUnit::Release() {
    ;
}

UpgradableUnit::UpgradableUnit(int id, std::string name, int price, int upgrade_price, int fine[])
    : MapUnit(id, name), host_(-1), level_(1), price_(price), upgrade_price_(upgrade_price) {
    for(int i = 0; i < Max_level_; ++i) {
        travel_fine_[i] = fine[i];
    }
}
Condition UpgradableUnit::Travel(int player) {// 回傳動作。
    MapUnit::Travel(player);
    if(player == host_){
        return UPGRADABLE;
    }
    else if(host_ == -1){
        return BUYABLE_U;
    }
    else if(player != host_){
        return PAYMENT_U;
    }
    else{
        return NOTHING;
    }
}
void UpgradableUnit::Map_Show(int num, int cont) const {
    MapUnit::Map_Show(num, cont);
    if(host_ != -1){
        std::cout<<"<"<<host_<<"> U$ ";
        
        std::cout<<std::setw(5)<<upgrade_price_<<" L"<<level_<<"    ";
    }
    else{
        std::cout<<"    B$ ";
        std::cout<<std::setw(5)<<price_<<"   "<<"    ";
    }
}
void UpgradableUnit::Release(){ //玩家id 
    host_ = -1;
    level_ = 1;
}
void UpgradableUnit::Upgrade(){
    level_ += 1;
}
void UpgradableUnit::Host(int player){
    host_ = player;
}

CollectableUnit::CollectableUnit(int id, std::string name, int price, int fine)
    :MapUnit(id, name), host_(-1), price_(price), travel_fine_(fine){
}
Condition CollectableUnit::Travel(int player) {// 回傳動作。
    MapUnit::Travel(player);
    if(player == host_){
        return NOTHING;
    } 
    else if(host_ == -1){
        return BUYABLE_C;
    }
    else if(player != host_){
        return PAYMENT_C;
    }
    else{
        return NOTHING;
    }
}
void CollectableUnit::Map_Show(int num, int cont) const {
    MapUnit::Map_Show(num, cont);
    if(host_ != -1){
        std::cout<<"<"<<host_<<"> x"<<cont<<" "<<"     "<<"   "<<"    "; //xn我不知道這個玩家有幾個Coll
    }
    else{
        std::cout<<"    B$ ";
        std::cout << std::setw(5) << price_<<"   "<<"    ";
    }
}
void CollectableUnit::Release(){ //玩家id 
    host_ = -1;
}
void CollectableUnit::Host(int player){
    host_ = player;
}

RandomCostUnit::RandomCostUnit(int id, std::string name, int price, int fine)
    :MapUnit(id, name), host_(-1), price_(price), travel_fine_(fine){
}
Condition RandomCostUnit::Travel(int player) {// 回傳動作。
    MapUnit::Travel(player);
    if(player == host_){
        return NOTHING;
    }
    else if(host_ == -1){
        return BUYABLE_R;
    }
    else if(player != host_){
        return PAYMENT_R;
    }
    else{
        return NOTHING;
    }
}
void RandomCostUnit::Map_Show(int num, int cont) const {
    MapUnit::Map_Show(num, cont);
    if(host_ != -1){
        std::cout<<"<"<<host_<<"> ?  "<<"     "<<"   "<<"    "; //xn我不知道這個玩家有幾個Coll
    }
    else{
        std::cout<<"    B$ ";
        std::cout<<std::setw(5)<<price_<<"   "<<"    ";
    }
};
void RandomCostUnit::Release(){ //玩家id 
    host_ = -1;
}
void RandomCostUnit::Host(int player){
    host_ = player;
}

JailUnit::JailUnit(int id, std::string name) 
    :MapUnit(id, name) {
}
Condition JailUnit::Travel(int player) {
    MapUnit::Travel(player);
    return JAIL;
}
void JailUnit::Map_Show(int num,int cont) const {
    MapUnit::Map_Show(num, cont);
    std::cout<<"JAIL   "<<"     "<<"   "<<"    ";
}