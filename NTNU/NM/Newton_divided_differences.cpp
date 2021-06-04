#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

struct Vector2d{
    double x;
    double y;
};

double NDD(vector<Vector2d> point, double x) {
    //


    int N = point.size();
    double f[N][N] = {0};
    double ans = 0;
    for(int i = 0; i < N; ++i) {
        double d;
        for(int j = 0; j < N-i; ++j) {
            if(i == 0)
                f[i][j] = point[j].y;
            else {
                f[i][j] = (f[i-1][j+1] - f[i-1][j]) / (point[j+i].x - point[j].x);
            }
        }
    }
    for(int i = 0; i < N; ++i) {
        printf("c[%d]=%lf\n", i, f[i][0]);
    }
    for(int i = N-1; i >= 0; --i) {
        ans *= (x - point[i].x);
        ans += f[i][0];
    }
    return ans;
}

int main() {
    // Interpolation Part 2
    // Newton_divided_differences
    // given N point to predict P(x) value
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
    printf("ans: %lf\n", NDD(point, x));
}

/*
4
1800 280
1850 283
1900 291
2000 370
1950
*/

/*
2019 fin
Part 1 (b)
4
-1 1
0 1
1 2
2 0
0
*/