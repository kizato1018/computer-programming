#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include "matrix.h"

using namespace std;

struct Vector2d{
    double x;
    double y;
};

double Lagrange(vector<Vector2d> point, double n) {
    //              (x-x2)(x-x3)          (x-x1)(x-x3)          (x-x1)(x-x2)   
    // P(x) = y1 * -------------- + y2 * -------------- + y3 * -------------- 
    //             (x1-x2)(x1-x3)        (x2-x1)(x2-x3)        (x3-x1)(x3-x2)  
    double ans = 0;
    for(int i = 0; i < point.size(); ++i) {
        double c = 1, d = 1;
        for(int j = 0; j < point.size(); ++j) {
            if(i != j) {
                c *= (n - point[j].x);
                d *= (point[i].x - point[j].x);
            }
        }
        ans += point[i].y * c / d;
    }

    return ans;
}

int main() {
    // Interpolation Part 1
    // Lagrange interpolation
    // Find an interpolating polynomial for the data points
    int N;
    double x;
    vector<Vector2d> point;
    Vector2d p;
    cout << "How many point: ";
    cin >> N;
    cout << "Input point: " << endl;
    while(N--) {
        cin >> p.x >> p.y;
        point.push_back(p);
    }
    cout << "predict point: ";
    cin >> x;
    // cout << "ans:" << Lagrange(point, x) << endl;
    printf("ans: %lf\n", Lagrange(point, x));
}

/*
4
1960 3039585530
1970 3707475887
1990 5281653820
2000 6079603571
1980
*/

/*
2019 fin 
Part 1 (a)
11
-5 5
-4 5
-3 5
-2 5
-1 5
0 5
1 5
2 5
3 5
4 5
5 42
6
*/