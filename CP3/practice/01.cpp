#include <stdio.h>

class Monster
{
public:
    void Create(int attack)
    {
        attack_ = attack;
        evolution_times_ = 1;
    }

    double Power() const
    {
        return evolution_times_ > 0 ? attack_/evolution_times_ : 0;
    }

	bool operator <(const Monster & M) {
		return Power() < M.Power();
	}

// TODO: operator +=

// TODO: operator +

private:
    int evolution_times_ = 0;
    double attack_ = 0;
};

int main()
{
    Monster bigfoot, vampire, slime;

    bigfoot.Create(40);
    vampire.Create(50);
    slime.Create(56);

    if (bigfoot < vampire && !(slime < vampire))
    {
        printf("Great! You may overloaded operator < correctly.\n");
    }

    Monster tmp = slime;
    (bigfoot += slime) += slime; // (40+56+56)/3

    if (tmp < slime || slime < tmp)
    {
        printf("Oh no, you should not modify slime.\n");
    }
    if (vampire < bigfoot)  // 50 < (40+56+56)/3
    {
        printf("Great! You may overloaded operator += correctly.\n");
    }
    if (bigfoot < vampire + slime) // 152/3 < 116/2
    {
        printf("Good. You have done the first step for overloading operator +.\n");
    }
    if (bigfoot < vampire) // 152/3 > 50/1
    {
        printf("Oh no, you should not modify vampire.\n");
    }
}
