#ifndef LARGE_NUMBER
#define LARGE_NUMBER
#include "Expr.h"
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

class LargeNumber
{
    friend class Expr;

public:
    // null constructor
    LargeNumber();
    // LargeNumber a("123456")
    LargeNumber(const string &raw);
    // copy constructor
    LargeNumber(const LargeNumber &ref);
    // destructor
    ~LargeNumber();

    // addition
    LargeNumber operator+(const LargeNumber &num) const;

    // substraction
    LargeNumber operator-(const LargeNumber &num) const;

    // multiplication
    LargeNumber operator*(const LargeNumber &num) const;

    // quotient
    LargeNumber operator/(const LargeNumber &num) const;

    // remainder
    LargeNumber operator%(const LargeNumber &num) const;

    // copier
    LargeNumber operator=(const LargeNumber &num);

    bool theformerisbigger(string &s1, string &s2) const;

    string number;
};

#endif