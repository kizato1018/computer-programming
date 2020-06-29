#include <string>
#include <vector>
#include "map_unit.h"

enum Condition { NOTHING, BUYABLE, PAY, UPGRADABLE, JAIL };

class MapUnit {
public:
    virtual Condition Travel(int player); // 回傳動作。
    virtual void Map_Show(); // format: [id] name 
private:
    int id_;
    string name_;
    vector<int> who_is_here_;
};
class UpgradableUnit : public MapUnit {
public:
    virtual Condition Travel(int player); // 回傳動作。
    virtual void Map_Show(){
        MapUnit::Map_Show();
    };
    void Release();
    int Buy_price() { return price_; }
    int Upgrade_price() { return upgrade_price_; }
    int Get_Host() { return host_; }
    int Get_Fine() { return travel_fine_[level_-1]; }

private:
    constexpr int Max_level_ = 5;
    int host_;
    int price_;
    int travel_fine_[Max_level_];
    int upgrade_price_;
    int level_;
};
class CollectableUnit : public MapUnit {
public:
    virtual Condition Travel(int player); // 回傳動作。
    void Release();
    int Get_Host() { return host_; }
    int Get_Fine() { return travel_fine_; }
private:
    int host_;
    int price_;
    int travel_fine_;
};
class RandomCostUnit : public MapUnit {
public:
    virtual Condition Travel(int player); // 回傳動作。
    void Release();
    int Get_Host() { return host_; }
    int Get_Fine() { return travel_fine_; }
private:
    int host_;
    int price_;
    int travel_fine_;

};
class JailUnit : public MapUnit {
public:
    virtual Condition Travel(int player); // 回傳動作。

};