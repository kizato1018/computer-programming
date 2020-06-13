#include <iostream>
#include <map>

using namespace std;

int main() {
    map<pair<int, int>, double> g;
    g.insert(pair<pair<int, int>, double>(pair<int, int>(1234,4321), 0.5));
    cout << g[pair<int,int>(1234, 4321)];
}