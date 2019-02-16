/*
 main.cpp
 Created by Jake Mathai on 2/4/2019.
 Copyright © 2019 Jake Mathai. All rights reserved.
 */

#include "bigint.h"
#include <cmath>
using std::cout;
using std::endl;

int main (int argc, char* argv[])
{
    unsigned long long digits = atoi (argv[1]);
    std::string num = argv[2] ;
    bigint a(digits,1), b(num);
    if (b.get_data().front() % 2 == 0)
    {
        cout << "Odd divisors not ending in 5 only." << endl;
        exit(1);
    }
    a = a * b;
    cout << a << " div " << b << ": ";
    bool k;
    auto start = std::chrono::steady_clock::now();
    k = div(a,b);
    auto end = std::chrono::steady_clock::now();
    cout << k << endl << a.get_data().size() << " digits in dividend." << endl;
    cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
    cout << " ms." << endl;
}
