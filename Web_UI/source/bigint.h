/*
 bigint.h
 Created by Jake Mathai on 2/4/2019.
 Copyright © 2019 Jake Mathai. All rights reserved.
 */

#ifndef bigint_h
#define bigint_h

#include <iostream>
#include <string>
#include <set>
#include <thread>
#include <list>
#include <iterator>

using std::list;
using std::string;
using std::cout;
using std::endl;

struct output
{
    output() {}
    output(const output& j)
    {
        return_val = j.return_val;
        dividend = j.dividend;
        dividend_size = j.dividend_size;
        divisor = j.divisor;
        divisor_size = j.divisor_size;
        runtime = j.runtime;
    }
    int return_val;
    string dividend;
    unsigned long long dividend_size;
    string divisor;
    unsigned long long divisor_size;
    unsigned long long runtime;
};

class bigint
{
public:
    bigint();   // Constructors
    bigint (string num);
    bigint (unsigned long long size, bool random);
    
    list<short>& get_data() { return data; }   // Reference to data
    
    friend std::ostream& operator << (std::ostream& out, const bigint& b);  // Outstream overload
    
    void operator ++(); // Increment
    
    bool operator < (const bigint& b) const;    // Comparison
    bool operator > (const bigint& b) const;
    bool operator == (const bigint& b) const;
    
    void operator = (const bigint& b) { data = b.data; } // Assignment
    friend void operator + (bigint& sum, bigint& b);    // Addition
    friend void operator - (bigint& diff, bigint& b);   // Subtraction
    
    friend bigint operator * (const bigint& b, short k); // Optimized multiplication functions
    friend bigint operator * (const bigint& b1, const bigint& b2); // for different contexts
    friend void compute_multiples (const bigint& b2, std::set<bigint>& multiples);
    friend void rule_multiply (bigint& product, const bigint& rule, short k);
    
    friend output div (bigint& b1, bigint& b2); // Div operator
    
private:
    list<short> data;  // Digits stored in reverse order in list
};
#endif /* bigint_h */
