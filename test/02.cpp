#include <iostream>
#include <cmath>

using namespace std;

class myClass{
public:
    int id;
    void Show();
    double Distance();
    void Set_x(int x) { 
        x_ = x;
    }
    void Set_y(int y) {
        y_ = y;
    }
private:
    int x_;
    int y_;
};

void myClass::Show() {
    cout << x_ << ", " << y_ << endl;
}

double myClass::Distance() {
    return sqrt(x_*x_ + y_*y_);
}

int main() {
    myClass p;
    p.id = 1;
    // p.x_ = 3; Error because it's myClass private member
    // p.y_ = -4; Error because it's myClass private member
    p.Set_x(3);
    p.Set_y(-4);
    cout << "p:";
    p.Show();
    cout << "dis=" << p.Distance() << endl;

}