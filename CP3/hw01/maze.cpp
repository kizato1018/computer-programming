#include "maze.h"

using namespace std;


void Maze::SetMap(const int W, const int H) {
    w = W;
    h = H;
    for(int i = 0; i < h; i++) {
        string s;
        cin >> s;
        Map.push_back(s);
    }
}

void Maze::PrintMap() const{
    for(int i = 0; i < h; i++) {
        cout << Map[i] << endl;
    }
}
