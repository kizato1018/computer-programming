#include <iostream>
#include <algorithm>
using namespace std;

class Card
{
    friend ostream & operator << (ostream &os, const Card &rhs);
    friend bool operator < (const Card &lhs, const Card &rhs);
public:
    void Set(char s, char d);
private:
    char suit_ = ' ', digit_ = ' ';
    int snum_ = 0, num_ = 0;
};
// ------------------------------------------------------------------
void Card::Set(char s, char d)
{
    suit_ = s;
    digit_ = d;
    switch (d) 
    {
    case '2' ... '9':
        num_ = d - '0';
        break;
    case 'T':
        num_ = 10;
        break;
    case 'J':
        num_ = 11;
        break;
    case 'Q':
        num_ = 12;
        break;
    case 'K':
        num_ = 13;
        break;
    case 'A':
        num_ = 14;
        break;
    default:
        break;
    }
    switch (s)
    {
    case 'C':
        snum_ = 0;
        break;
    case 'D':
        snum_ = 1;
        break;
    case 'S':
        snum_ = 2;
        break;
    case 'H':
        snum_ = 3;
        break;
    default:
        break;
    }
}
// ------------------------------------------------------------------
bool operator < (const Card &lhs, const Card &rhs)
{
    if(lhs.snum_ < rhs.snum_) return true;
    else if(lhs.snum_ > rhs.snum_) return false;
    else if(lhs.num_ < rhs.num_) return true;
    else return false;
}
// ------------------------------------------------------------------
ostream & operator << (ostream &os, const Card &card)
{
    os << card.suit_ << card.digit_;
    return os;
}
// ------------------------------------------------------------------
int main()
{
    char start = ' ';
    while (cin >> start && start!='#')
    {
        constexpr char position[] = "NESW";
        constexpr size_t NumPeople = sizeof(position)-1;

        // determine the first player to get cards
        int j = 0;
        for (size_t i=0; i<NumPeople; i+=1)
        {
            if (position[i]==start)
            {
                j = (i+1)%NumPeople;
                break;
            }
        }

        // read in and distribute cards
        constexpr size_t NumCards = 13;
        Card cards[NumPeople][NumCards];
        for (size_t i=0; i<NumPeople*NumCards; i+=1)
        {
            char s, n;
            cin >> s >> n;
            cards[j][i/NumPeople].Set(s, n);
            j = (j+1)%NumPeople;
        }

        // sort cards of every player
        for (size_t j=0; j<NumPeople; j+=1)
        {
            sort(cards[j], cards[j]+NumCards);
        }

        // find the first player to display
        for (size_t i=0; i<NumPeople; i+=1)
        {
            if (position[i]=='S')
            {
                j = i;
                break;
            }
        }

        // display cards of every player
        for (size_t t=0; t<NumPeople; t+=1, j=(j+1)%NumPeople)
        {
            cout << position[j] << ':';
            for (size_t i=0; i<NumCards; i+=1)
            {
                cout << ' ' << cards[j][i];
            }
            cout << endl;
        }
    }
}
/*
N
CQDTC4D8S7HTDAH7D2S3D6C6S6D9S4SAD7H2CKH5D3CTS8C9H3C3
DQS9SQDJH8HAS2SKD4H4S5C7SJC8DKC5C2CAHQCJSTH6HKH9D5HJ
S
CQDTC4D8S7HTDAH7D2S3D6C6S6D9S4SAD7H2CKH5D3CTS8C9H3C3
DQS9SQDJH8HAS2SKD4H4S5C7SJC8DKC5C2CAHQCJSTH6HKH9D5HJ
#
*/