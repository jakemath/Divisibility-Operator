/*
 bigint.cpp
 Created by Jake Mathai on 2/4/2019.
 Copyright © 2019 Jake Mathai. All rights reserved.
 */

#include "bigint.h"

bigint::bigint() {}   // Default constructor

bigint::bigint (string num)    // String constructor
{
    for (unsigned long long i = 0; i < num.length(); ++i)
        data.push_back(num[num.length() - 1 - i] - '0');
}

bigint::bigint (unsigned long long size, bool random)    // Random number constructor
{                                                        // OR 0 filled constructor
    unsigned long long i = 1;
    if (random) // Random number specified
    {
        srand(time(0)); // First seed for first half of number
        if (size == 1)
        {
            ++size;
            for (; i <= size/2; ++i)
                data.push_back(rand() % 10);
        }
        else
        {
            for (; i <= size/2; ++i)
                data.push_back(rand() % 10);
            srand(time(0)); // Second seed for second half of number
            for (; i <= size; ++i)
                data.push_back(rand() % 10);
        }
        if (data.back() == 0)   // Ensure most significant digit is not 0
        {
            for (; data.back() == 0;)
                data.back() = rand() % 10;
        }
    }
    else    // 0-filled specified
    {
        for (; i <= size; ++i)
            data.push_back(0);
    }
}

void operator + (bigint& sum, bigint& b)  // Overloaded addition. Result stored in sum argument
{
    if (b.data.back() != 0) // In this program we mark a number as 0 by making the most significant
    {                       // digit 0. If it is 0 --> no execution
        if (!sum.negative() && b.negative())    // A + (-B) = A - B
        {
            b.negate();
            sum - b;
        }
        else
        { // carry stores potential overflow at each digit, temp holds result of sum at each digit
            short carry = 0, temp;
            list<short>::iterator i = sum.data.begin(), j = b.data.begin();
            for (; i != sum.data.end() && j != b.data.end(); ++i, ++j)
            {
                temp = *i + *j + carry;
                if (temp > 9)   // If temp > 9 --> carry = 1, store temp - 10
                {
                    *i = temp - 10;
                    carry = 1;
                }
                else    // If temp < 10 --> store temp
                {
                    *i = temp;
                    carry = 0;
                }
            }
            if (i != sum.data.end() && j == b.data.end())   // If sum has more digits than b, compute
            {                                               // the rest of digits while a carry of 1 exists
                for (; i != sum.data.end() && carry == 1; ++i)  // No need to continue once a carry of 0 occurs
                {
                    temp = *i + carry;
                    if (temp > 9)
                    {
                        *i = temp - 10;
                        carry = 1;
                    }
                    else
                    {
                        *i = temp;
                        carry = 0;
                    }
                }
            }
            /*
             else if (i == sum.data.end() && j != b.data.end())  // If sum has less digits than b --> push_back
             {                                                   // the rest of the results
             for (; j != b.data.end(); ++j)
             {
             temp = *j + carry;
             if (temp > 9)
             {
             sum.data.push_back(temp - 10);
             carry = 1;
             }
             else
             {
             sum.data.push_back(temp);
             carry = 0;
             }
             }
             }
             */
            if (carry != 0) // If carry exists after computing each digit --> add a new digit of 1
                sum.data.push_back(carry);
        }
    }
}

void operator - (bigint& diff, bigint& b)  // Overloaded subtraction. Result stored in diff argument
{
    if (b.data.back() != 0) // No execution if subtracting 0
    {
        if (diff < b)   // Negative results defaulted to -1
            diff.data.back() = -1;
        else if (diff == b) // If same number --> 0
            diff.data.back() = 0;
        else
        {
            short temp; // Temp holds result of subtraction at each digit
            list<short>::iterator i = diff.data.begin(), j = b.data.begin();
            for (; i != diff.data.end() && j != b.data.end(); ++i, ++j)
            {
                temp = *i - *j;
                if (temp < 0)   // If negative result --> find the first non-zero digit after the current
                {               // digit to optimize borrowing
                    list<short>::iterator k = i;   // Iterate from current digit
                    if (*i != 0)    // If current digit non-zero --> ignore
                        ++k;
                    for (; *k == 0; ++k)    // Switch all 0 digits to 9 until a non-zero digit is found
                        *k = 9;
                    --*k;   // Decrement first non-zero digit to borrow from it
                    *i = temp + 10; // Add borrow to the current digit
                }
                else    // If positive result --> store temp
                    *i = temp;
            }
            if (diff.data.back() == 0)  // If subtracting same sized numbers --> most significant digit
            {                           // may result in 0 and will need to be removed
                for (; diff.data.back() == 0 && !diff.data.empty();)    // While the most significant digit is 0, pop_back()
                    diff.data.pop_back();
                if (diff.data.empty())  // If the whole number was cleared, return 0
                    diff.data.push_back(0);
            }
        }
    }
}

void bigint::operator ++()  // Overloaded pre-increment.
{
    if (data.front() != 9)  // If ones digit not 9 --> increment
        ++data.front();
    else    // If ones digit 9 --> find first non-nine digit to add the carry to
    {
        list<short>::iterator i = data.begin();
        for (; i != data.end() && *i == 9; ++i) // Switch all nine digits to 0 until first non-nine digit found
            *i = 0;
        if (i != data.end())    // If not at the end of number --> increment
            *i += 1;
        else    // If at end of number --> add a digit
            data.push_back(1);
    }
}

bigint operator * (const bigint& b, int k)  // General overloaded multiplication
{
    if (k == 0 || b.data.back() == 0)   // If multiplying by 0 --> return 0
        return bigint("0");
    bigint product; // Store result in product
    if (k < 10) // If k < 10 --> no recursion
    { // Temp holds result of digit multiplication, carry holds potential overflow from temp
        short temp, carry = 0;
        list<short>::const_iterator i = b.data.begin();
        for (; i != b.data.end(); ++i)
        {
            temp = (abs(*i) * k) + carry;  // Use abs and worry about negativity after
            if (temp > 9)   // If temp > 10 --> store ones digit of temp and let carry = temp / 10.
            {               // So if temp = 81 --> result = 1, carry = 8
                product.data.push_back(temp % 10);
                carry = temp / 10;
            }
            else    // If temp < 10 --> store result
            {
                product.data.push_back(temp);
                carry = 0;
            }
        }
        if (carry != 0) // push_back any leftover carry after iterating
            product.data.push_back(carry);
    }
    else if (k == 10)   // Multiplying by 10 is the same as adding a leading 0
    {
        product = b;
        product.data.push_front(0);
    }
    else    // k > 10 --> recurse and add (b * ones digit of k) + (b * k / 10)
    {
        bigint l = b * (k % 10), r = b * (k / 10) * 10;
        r + l;
        if ((b.negative() && k > 0) || (!b.negative() && k < 0))    // Account for differing signs
            r.negate();
        return r;   // Return local r
    }
    if ((b.negative() && k > 0) || (!b.negative() && k < 0))    // Account for differing signs
        product.negate();
    return product;
}

bigint operator * (const bigint& b1, const bigint& b2)    // Bigint multiplication, similar principle as above
{
    if (b1.data.back() == 0 || b2.data.back() == 0)
        return bigint("0");
    bigint product;
    if (b2.data.size() >= 2)
    {
        if (b2.data.size() == 2 && b2.data.front() == 0 && (b2.data.back() == 1 || b2.data.back() == -1))
        {
            product = b1;
            product.data.push_front(0);
        }
        else
        {
            product = b2;
            product.data.pop_front();
            bigint l = b1 * b2.data.front(), r = (b1 * product) * 10;
            r + l;
            return r;
        }
    }
    else
    {
        short temp, carry = 0;
        list<short>::const_iterator i = b1.data.begin();
        for (; i != b1.data.end(); ++i)
        {
            temp = (abs(*i) * b2.data.front()) + carry;
            if (temp > 9)
            {
                product.data.push_back(temp % 10);
                carry = temp / 10;
            }
            else
            {
                product.data.push_back(temp);
                carry = 0;
            }
        }
        if (carry != 0)
            product.data.push_back(carry);
    }
    if (b1.negative() != b2.negative())
        product.negate();
    return product;
}

void rule_multiply (bigint& product, const bigint& rule, short k)   // Specialized pass-by-reference multiplication function.
{                                             // Result stored in product and rule remains unchanged. Similar principle as above
    if (k == 0) // Multiplication by 0
        product.data.back() = 0;
    else
    {
        short temp, carry = 0;
        list<short>::const_iterator i = rule.data.begin();
        list<short>::iterator j = product.data.begin();
        for (; i != rule.data.end() && j != product.data.end(); ++i, ++j)
        {
            temp = (abs(*i) * k) + carry;
            if (temp > 9)
            {
                *j = temp % 10;
                carry = temp / 10;
            }
            else
            {
                *j = temp;
                carry = 0;
            }
        }
        if (i == rule.data.end() && j != product.data.end())
        {
            if (carry != 0)
            {
                *j = carry;
                carry = 0;
            }
            else
                --j;
            list<short>::iterator k = std::next (product.data.end(), -1);
            for (; j != k;)
            {
                product.data.pop_back();
                k = std::next (product.data.end(), -1);
            }
        }
        else if (i != rule.data.end() && j == product.data.end())
        {
            for (; i != rule.data.end(); ++i)
            {
                temp = (abs(*i) * k) + carry;
                if (temp > 9)
                {
                    product.data.push_back(temp % 10);
                    carry = temp / 10;
                }
                else
                {
                    product.data.push_back(temp);
                    carry = 0;
                }
            }
        }
        if (carry != 0)
            product.data.push_back(carry);
        if (rule.negative())
            product.negate();
    }
}

bool bigint::operator < (const bigint& b) const // < only used for positive comparison in subtraction
{
    if (data.size() != b.data.size())
    {
        if (data.size() > b.data.size())
            return false;
        return true;
    }
    if (data.back() > b.data.back())
        return false;
    if (data.back() < b.data.back())
        return true;
    list<short>::const_reverse_iterator i = ++data.rbegin(), j = ++b.data.rbegin();
    for (; i != data.rend() && j != b.data.rend(); ++i, ++j)
    {
        if (*i < *j)
            return true;
        if (*i > *j)
            return false;
    }
    return false;
}

bool bigint::operator > (const bigint& b) const // > only used to compare to a positive number in div loop
{
    if (data.back() == 0)
        return false;
    if (negative() != b.negative())
    {
        if (negative() && !b.negative())
            return false;
        return true;
    }
    if (data.size() != b.data.size())
    {
        if (data.size() < b.data.size())
            return false;
        return true;
    }
    if (data.back() < b.data.back())
        return false;
    if (data.back() > b.data.back())
        return true;
    list<short>::const_reverse_iterator i = ++data.rbegin(), j = ++b.data.rbegin();
    for (; i != data.rend() && j != b.data.rend(); ++i, ++j)
    {
        if (*i < *j)
            return false;
        if (*i > *j)
            return true;
    }
    return false;
}

bool bigint::operator == (const bigint& b) const
{
    if (data.size() != b.data.size() || data.back() != b.data.back() || data.front() != b.data.front() || negative() != b.negative())
        return false;
    list<short>::const_iterator i = ++b.data.begin(), j = ++data.begin();
    for (; i != b.data.end() && j != data.end(); ++i, ++j)
    {
        if (*i != *j)
            return false;
    }
    return true;
}

bool div (bigint& b1, bigint& b2)   // Div operator
{
    if (b2.data.size() == 1 && b2.data.back() != 7 && b2.data.back() != 9)    // Special cases: 2, 3, and 5
    {
        if (b2.data.front() == 2)   // div by 2
        {
            if (b1.data.front() % 2 == 0)
                return true;
            return false;
        }
        if (b2.data.front() == 3)   // div by 3
        {
            unsigned long long total = 0;
            list<short>::iterator i = b1.data.begin();
            for (; i != b1.data.end(); ++i)
                total += *i;
            if (total % 3 == 0)
                return true;
            return false;
        }
        if (b1.data.front() == 0 || b1.data.front() == 5)   // div by 5
            return true;
        return false;
    }
    else if (b1.data.size() >= b2.data.size())
    {
        bigint rule;
        if (b2.data.front() == 1 || b2.data.front() == 9)
            rule = b2;
        else
            rule = b2 * 3;
        bigint twentieth_multiple = b2 * 20; // Set threshold size for iterations
        // Compute rule of b2, and create a 0-filled bigint product to store the results of (rule * ones digit) at each iteration
        if (rule.data.front() == 1)
        {
            rule.data.pop_front();
            rule.negate();
        }
        else
        {
            if (rule.data.size() > 1)
                rule.data.pop_front();
            ++rule;
        }
        bigint product(rule.data.size() - 1, 0);
        short ones; // Variable for ones digit
        void (*arith)(bigint&, bigint&);
        if (rule.negative())
        {
            rule.negate();
            arith = operator -;
        }
        else
            arith = operator +;
        for (; b1 > times_twenty;)  // Iterate until within bounds of the set
        {
            ones = b1.data.front();
            b1.data.pop_front();
            rule_multiply(product, rule, ones); // product = rule * ones
            arith(b1, product);   // b1 = b1.chopped() + product or b1 = b1.chopped() - product
        }
        if (b1.data.back() == 0 || b1 == b2 || b1 == times_twenty) // If in the set --> is divisible
            return true;
        for (int i = 2; i < 20; ++i)
        {
            if (b2 * i == b1)
                return true;
        }
    }
    return false;
}

std::ostream& operator <<(std::ostream& out, const bigint& b)   // Outstream overload
{
    for (std::list<short>::const_reverse_iterator i = b.data.rbegin(); i != b.data.rend(); ++i)
        out << *i;
    return out;
}
