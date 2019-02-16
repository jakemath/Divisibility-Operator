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
#include <list>
#include <iterator>

class bigint
{
public:
    bigint();   // Constructors
    bigint (std::string num);
    bigint (unsigned long long size, bool random);
    
    bool negative() const { return (data.back() < 0); } // Negativity
    
    std::list<short>& get_data() { return data; }   // Reference to data
    
    friend std::ostream& operator << (std::ostream& out, const bigint& b);  // Outstream overload
    
    void negate() { data.back() *= -1; }    // *= -1
    
    void operator ++(); // Increment
    
    bool operator < (const bigint& b) const;    // Comparison
    bool operator > (const bigint& b) const;
    bool operator == (const bigint& b) const;
    
    void operator = (const bigint& b) { data = b.data; }    // Assignment
    friend void operator + (bigint& sum, bigint& b);    // Addition
    friend void operator - (bigint& diff, bigint& b);   // Subtraction
    
    friend bigint operator * (const bigint& b, int k);  // Optimized multiplication functions for different contexts
    friend bigint operator * (const bigint& b1, const bigint& b2);
    void make_rule_multiply (short k);
    friend void rule_multiply (bigint& product, const bigint& rule, short k);
    
    friend bigint make_rule (bigint b); // Rule generator
    friend bool div (bigint b1, bigint b2); // Div operator
    
private:
    std::list<short> data;  // Digits stored in reverse order in list
};

#endif /* bigint_h */
