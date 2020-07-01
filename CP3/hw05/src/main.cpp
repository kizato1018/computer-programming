#include "game.h"
#include <unistd.h>

using namespace std;

int main() {
    ifstream map_s("map.dat", ifstream::in);
    Game game;
    game.Init(map_s);
    int cur_player = 0;
    int total_player = game.Get_Total_Player();
    Condition event;
    while(!game.Is_Game_Over()) {
        system("clear");
        game.Show_Info(cur_player);
        event = game.Move(cur_player);
        if(event == BANKRUPT){
            cur_player=(cur_player+1)%total_player;
            continue;
        }
        system("clear");
        game.Show_Info(cur_player);
        if(game.Is_Game_Over()){ return 0;}
        game.Travel(cur_player, event);
        cur_player=(cur_player+1)%total_player;
    }
    return 0;
}
