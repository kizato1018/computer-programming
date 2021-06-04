#ifndef __MAP_UNIT_H__
#define __MAP_UNIT_H__

#include <iostream>
#include <string>
#include <vector>

enum Condition { NOTHING, BUYABLE_U , BUYABLE_C , BUYABLE_R , PAYMENT_U, PAYMENT_C, PAYMENT_R, UPGRADABLE, JAIL, BANKRUPT};

class MapUnit {
public:
    MapUnit(int , std::string );
    virtual Condition Travel(int); // 回傳動作。
    void Leave(int);
    virtual void Map_Show(int, int) const;
    virtual void Release();
    virtual int Get_Host() const { return -1; }
    virtual int Get_Fine() const { return 0; }
    std::string Get_Unit_Name() const { return name_; }
protected:
    unsigned int who_is_here_; //bit
    int id_;
    std::string name_;
private:
};
class UpgradableUnit : public MapUnit {
public:
	UpgradableUnit(int ,std::string ,int ,int ,int[] );
    virtual Condition Travel(int );
    virtual void Map_Show(int ,int) const;
    virtual void Release();
    void Upgrade();
    int Buy_price() const { return price_; }
    int Upgrade_price() const { return upgrade_price_; }
    virtual int Get_Host() const { return host_; }
    virtual int Get_Fine() const { return travel_fine_[level_-1]; }
    int Get_Level() const { return level_; }
    void Host(int );
private:
    static constexpr int Max_level_ = 5;
    int host_;
    int price_;
    int travel_fine_[Max_level_];
    int upgrade_price_;
    int level_;
};

class CollectableUnit : public MapUnit {
public:
    CollectableUnit(int ,std::string ,int ,int );
	virtual Condition Travel(int );
    virtual void Map_Show(int ,int) const;
    virtual void Release();
    int Buy_price() const { return price_; }
    virtual int Get_Host() const { return host_; }
    virtual int Get_Fine() const { return travel_fine_; }
    void Host(int );
private:
    int host_;
    int price_;
    int travel_fine_;
};
class RandomCostUnit : public MapUnit {
public:
    RandomCostUnit(int ,std::string ,int ,int );
	virtual Condition Travel(int );
	virtual void Map_Show(int ,int) const;
    virtual void Release();
    int Buy_price() const { return price_; }
    virtual int Get_Host() const { return host_; }
    virtual int Get_Fine() const { return travel_fine_; }
    void Host(int );
private:
    int host_;
    int price_;
    int travel_fine_;

};
class JailUnit : public MapUnit {
public:
    JailUnit(int ,std::string );
    virtual Condition Travel(int );
    virtual void Map_Show(int, int) const;
};
#endif