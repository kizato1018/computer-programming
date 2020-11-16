#include <iostream>
#include <stack>
#include <conio.h> 

using namespace std;

int main() {
    string str, tmp;
    char c;
    while((c = getch()) != 27) {
        cout << c;
        cin >> tmp;
        str = c + tmp;
        cout << str;
    }
}
