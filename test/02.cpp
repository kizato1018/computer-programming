#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int a[3] = {1,2,3};
    reverse(a, a+3);
    for(int i = 0; i < 3; i++)
        cout << a[i] << " ";
}