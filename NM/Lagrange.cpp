#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

struct Vector2d{
    double x;
    double y;
};

double Lagrange(vector<Vector2d> point, double n) {
    double ans = 0;
    // vector<double> poly;
    for(int i = 0; i < point.size(); ++i) {
        double c = 1, d = 1;
        for(int j = 0; j < point.size(); ++j) {
            if(i != j) {
                c *= (n - point[j].x);
                d *= (point[i].x - point[j].x);
            }
        }
        ans += point[i].y * c / d;
        // for(int j = 0; j < point.size(); ++j) {
        //     if(i != j) {
        //         if(poly.empty()) poly.push_back(1);
        //         for(int k = 0; k <= j; ++k) {
        //             poly[k] += poly[k] * point[j].x * -1;
        //             if(k > 0)
        //                 poly[k] += 
        //         }
        //         poly.push_back(1);

        //     }
        // }
    }

    return ans;
}

int main() {
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