#include "maze.h"

using namespace std;


Maze::Maze(const int W, const int H) {
    w = W;
    h = H;
}

void Maze::SetMap() {
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
