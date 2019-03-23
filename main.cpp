/*
 main.cpp
 Created by Jake Mathai on 2/4/2019.
 Copyright © 2019 Jake Mathai. All rights reserved.
 */

#include "bigint.h"

int main (int argc, char* argv[])
{
    unsigned long long digits = atoi(argv[1]);
    string num = argv[2];
    bigint a(digits,1), b(num);
    if (b.get_data().front() % 2 == 0 || (b.get_data().front() == 5 && b.get_data().size() > 1))
    {
        cout << "Only ddd divisors not ending in 5 allowed." << endl;
        exit(1);
    }
    a = a * b;
    cout << endl << a << " div " << b << ":" << endl << endl;
    bool k;
    auto start = std::chrono::steady_clock::now();
    k = div(a,b);
    auto end = std::chrono::steady_clock::now();
    cout << "Return value: " << k << endl << "Digits in dividend: " << a.get_data().size() << endl;
    cout << "Digits in divisor: " << b.get_data().size() << endl;
    cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
    cout << " ms" << endl << endl;
}
