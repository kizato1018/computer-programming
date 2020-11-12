#include "expression.h"
#include <iostream>

using namespace std;

int main() {
    expression exp1;
    string str;
    cin >> str;
    cout << exp1.GetExpression(str);
}