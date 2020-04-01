#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

struct Pos{
	int x;
	int y;
	Pos operator+(Pos tar) { return Pos{.x = x + tar.x, .y = y + tar.y}; }
	Pos operator-(Pos tar) { return Pos{.x = x - tar.x, .y = y - tar.y}; }
	void operator=(Pos tar) { x = tar.x, y = tar.y; }
};

int main()
{
    int P; // number of players in the game (2 to 4 players)
    int ID; // ID of your player (0, 1, 2, or 3)
    int D; // number of drones in each team (3 to 11)
    int Z; // number of zones on the map (4 to 8)
    vector<Pos> drones; 
    cin >> P >> ID >> D >> Z; cin.ignore();
    for (int i = 0; i < Z; i++) {
        int X; // corresponds to the position of the center of a zone. A zone is a circle with a radius of 100 units.
        int Y;
        cin >> X >> Y; cin.ignore();
    }

    // game loop
    while (1) {
        for (int i = 0; i < Z; i++) {
            int TID; // ID of the team controlling the zone (0, 1, 2, or 3) or -1 if it is not controlled. The zones are given in the same order as in the initialization.
            cin >> TID; cin.ignore();
        }
        for (int i = 0; i < P; i++) {
            for (int j = 0; j < D; j++) {
                int DX; // The first D lines contain the coordinates of drones of a player with the ID 0, the following D lines those of the drones of player 1, and thus it continues until the last player.
                int DY;
                cin >> DX >> DY; cin.ignore();
                
            }
        }
        for (int i = 0; i < D; i++) {
            
            // Write an action using cout. DON'T FORGET THE "<< endl"
            // To debug: cerr << "Debug messages..." << endl;


            // output a destination point to be reached by one of your drones. The first line corresponds to the first of your drones that you were provided as input, the next to the second, etc.
            cout << "20 20" << endl;
        }
    }
}