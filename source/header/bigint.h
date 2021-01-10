/*
 bigint.h
 Created by Jake Mathai on 2/4/2019.
 Copyright © 2019 Jake Mathai. All rights reserved.
 */

#ifndef bigint_h
#define bigint_h

#include <set>
#include <list>
#include <string>
#include <random>
#include <numeric>
#include <iterator>
#include <iostream>

using std::list;
using std::cout;
using std::endl;
using std::string;

class bigint {
public:
    bigint();
    bigint(string num);
    bigint(unsigned long long size, bool randomize);
    friend std::ostream& operator << (std::ostream& out, const bigint& b);  // Outstream overload
    void operator ++(); // Pre-increment operator
    bool operator < (const bigint& b) const;  // Optimized comparison operators
    bool operator > (const bigint& b) const;
    bool operator == (const bigint& b) const { return digits == b.digits; }
    void operator = (const bigint& b) { digits = b.digits; }    // Assignment operator
    friend void operator + (bigint& sum, bigint& b);    // Addition
    friend void operator - (bigint& result, bigint& b);   // Subtraction
    friend bigint operator * (const bigint& b, short k); // Scalar multiplication
    friend bigint operator * (const bigint& b1, const bigint& b2); // Bigint multiplication
    friend void rule_multiply(bigint& product, const bigint& rule, short k); // Optimized inplace scalar multiplication
    friend bool div(bigint& dividend, bigint& divisor); // Div operator
    list<short> digits;  // Digits stored in reverse order in list
};

#endif /* bigint_h */
