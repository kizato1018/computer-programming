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
        if(express.GetExpression(str)) {
            continue;
        }
        express.Show();
        cout << "result:" << express.GetResult() << endl;
    }
    return 0;
}