#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point{
    int x;
    int y;
    friend ostream& operator<< (ostream &os, const Point &a){ return os << "(" << a.x << "," << a.y << ")"; }
};

double dis(Point a, Point b) {
    return sqrt(pow(a.x-b.x, 2) + pow(a.y-b.y, 2)) + 16;
}

int main() {
    int N;
    int cnt = 0;
    while(cin >> N && N) {
        Point a[100];
        int permutation[100] = {0};
        int Min[100] = {0};
        double Minsum = 100000;
        for(size_t i = 0; i < N; ++i)
            cin >> a[i].x >> a[i].y;
        iota(permutation, permutation+N, 0);
        do {
            double sum = 0;
            for(size_t i = 1; i < N; ++i) 
                sum += dis(a[permutation[i-1]], a[permutation[i]]);
            if(sum < Minsum) {
                copy(permutation, permutation+N, Min);
                Minsum = sum;
            }
        } while(next_permutation(permutation, permutation+N));
        cout << "**********************************************************" << endl;
        cout << "Network #" << ++cnt << endl;
        for(size_t i = 1; i < N; ++i) 
            cout << "Cable requirement to connect " << a[Min[i-1]] << " to " << a[Min[i]] << " is " << fixed << setprecision(2) << dis(a[Min[i-1]], a[Min[i]]) << " feet." << endl;
        cout << "Number of feet of cable required is " << fixed << setprecision(2) << Minsum << "." << endl;        
        
    }
    
}