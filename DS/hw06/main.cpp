#include "expression.h"
#include <iostream>
#include <conio.h> 

using namespace std;

int main() {
    char c;
    string str, tmp;
    // while(getline(cin, str));
    while((c = getch()) != 27) {
        expression express;
        cout << c;
        cin >> tmp;
        str = c + tmp;
        cout << express.GetExpression(str) << endl;
        express.Show();
        cout << "result:" << express.GetResult() << endl;
    }
}