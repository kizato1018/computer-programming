#include "expression.h"
#include <iostream>
#include <conio.h> 

using namespace std;

bool Input(string &s) {
    s = "";
    char c;
    int cnt = 0;
    while(1) {
        c = getch();
        if(c == 27) return false;
        else if(c == '\r' || c == '\n') break;
        else if(c == 8) {
            if(cnt > 0) {
                cout << c << " " << c;
                --cnt;
            }
            if(!s.empty())
                s.pop_back();
            // cout << cnt << endl;
            continue;
        }
        else {
            ++cnt;
            cout << c;
            s += c;
        }
    }
    cout << endl;
    return true;
}

int main() {
    string str;
    // while(getline(cin, str));
    cout << "Please enter an infix expression and press enter:";
    while(Input(str)) {
        if(str.empty()) continue;
        expression express;
        if(express.GetExpression(str)) {
            cout << "Please enter an infix expression and press enter:";
            continue;
        }
        cout << "The postfix expression:";
        express.Show();
        cout << "=" << express.GetResult() << endl;
        cout << "Please enter an infix expression and press enter:";
    }
    return 0;
}