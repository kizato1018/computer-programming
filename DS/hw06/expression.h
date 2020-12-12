#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__
#include <string>
#include "bintree.h"


class expression {
public:
    expression() {}
    bool GetExpression(const std::string&);
    bool GetExpression(const char* s) { return GetExpression(std::string(s)); }
    double GetResult() { return result_; }
    void Show();
private:
    bool CheckExpression_(const std::string&);
    int Getoperand_(const std::string&, int);
    char Getoperator_(const std::string&, int);
    expretree expre_;
    double result_;
};

#endif