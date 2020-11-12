#include "expression.h"
#include <iostream>
#include <algorithm>
#include <ctype.h>

using namespace std;

int expression::CheckExpression_(const string s) {
    size_t np = string::npos;
    if(s.find_first_not_of("0123456789()+-*/") != np) {
        cout << "Illegal character" << endl;
        return 1;
    }
    if(string("+-*/").find(*s.begin()) != np) {
        cout << "First character an operator" << endl;
        return 2;
    }
    for(int index = 0; ; ++index) {
        index = s.find_first_of("+-*/", index);
        if(index == np || index+1 > s.length()) break;
        if(string("+-*/").find(s[index+1]) != np) {
            cout << "Operator followed by an operator" << endl;
            return 5;
        }
    }
    if(string("+-*/").find(*s.rbegin()) != np) {
        cout << "Last character an operator" << endl;
        return 3;
    }
    for(int index = 0;;++index) {
        index = s.find(")", index);
        if(index == np || index+1 > s.length()) break;
        if(isdigit(s[index+1])) {
            cout << "Right parenthesis followed by an identifier" << endl;
            return 4;
        }
        if(s[index+1] == '(') {
            cout << "Right parenthesis followed by a left parenthesis" << endl;
            return 8;
        }
        if(index > 0 && string("+-*/").find(s[index-1]) != np) {
            cout << "Operator followed by a left parenthesis" << endl;
            return 9;
        }
    }
    for(int index = 0; ; ++index) {
        index = s.find("(", index);
        if(index == np || index+1 > s.length()) break;
        if(string("+-*/").find(s[index+1]) != np) {
            cout << "Left parenthesis followed by an operator" << endl;
            return 6;
        }
        if(index > 0 && isdigit(s[index-1])) {
            cout << "Identifier followed by a left parenthesis" << endl;
            return 7;
        }
    }
    for(int index = 1; index < s.length(); ++index) {
        index = s.find("(", index);
        if(index == np) break;
        if(isdigit(s[index-1])) return 7;
    }
    if(s.find("()") != np) {
        cout << "Left parenthesis followed by a right parenthesis" << endl;
        return 10;
    }
    int lcnt = 0, rcnt = 0;
    for(int index = 0; index < s.length(); ++index) {
        lcnt += (s[index] == '(');
        rcnt += (s[index] == ')');
    }
    if(lcnt > rcnt) {
        cout << "Unmatched left parenthesis" << endl;
        return 11;
    }
    if(rcnt > lcnt) {
        cout << "Unmatched right parenthesis" << endl;
        return 12;
    }
    return 0;
}

int expression::Getoperand_(const string s, int index) {
    int digit = s.find_first_not_of("0123456789", index);
    if(digit == string::npos) digit = s.length();
    string str = s.substr(index, digit-index);
    int val = 0;
    for(auto i = str.rbegin(); i != str.rend(); ++i) {
        val = val * 10 + (*i);
    }
    return val;
}

char expression::Getoperator_(const string s, int index) {
    return s[index];
}

int expression::GetExpression(const string s) {
    if(int r = CheckExpression_(s)) return r;
    for(int i = 0; i < s.length(); ++i) {
        if(isdigit(s[i]))
            operand_.push(Getoperand_(s, i));
        else 
            operator_.push(Getoperator_(s, i));
    }
    return 0;
}