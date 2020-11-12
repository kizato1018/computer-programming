#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__
#include <string>
#include <stack>


class expression {
public:
    expression() {}
    int GetExpression(const std::string);
    int GetExpression(const char* s) { return GetExpression(std::string(s)); }
private:
    int CheckExpression_(const std::string);
    int Getoperand_(const std::string, int);
    char Getoperator_(const std::string, int);
    std::stack<int> operand_;
    std::stack<char> operator_;
};

#endif