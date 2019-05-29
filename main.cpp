/*
 main.cpp
 Created by Jake Mathai on 2/4/2019.
 Copyright © 2019 Jake Mathai. All rights reserved.
 */

#include "bigint.h"

int main (int argc, char* argv[])
{
    unsigned long long d = atoi(argv[1]), divsr_size = atoi(argv[2]);
    unsigned long long a_size;
    if (d < divsr_size)
    {
        cout << "Dividend size must be >= divisor size" << endl;
        exit(1);
    }
    else if (d == divsr_size)
        a_size = 1;
    else
        a_size = d - divsr_size;
    bigint a(a_size, 1), b(divsr_size, 1);
    // Check for faulty inputs
    short odds[4] = {3,7,9,1};
    if (b.get_data().front() % 2 == 0)
    {
        srand(time(0));
        if (b.get_data().size() > 1)
            b.get_data().front() = odds[rand() % 4];
        else if (b.get_data().size() == 1 && b.get_data().front() != 2)
            b.get_data().front() = odds[rand() % 3];
    }
    else if (b.get_data().front() == 5 && b.get_data().size() > 1)
        b.get_data().front() = odds[rand() % 4];
    else if (b.get_data().front() == 1 && b.get_data().size() == 1)     // If divisor is 1
        b.get_data().front() = odds[rand() % 3];
    a = a * b;
    unsigned long long digits1 = a.get_data().size();
    cout << endl << a << " div " << b << ":" << endl << endl;
    bool k;
    auto start = std::chrono::steady_clock::now();
    k = div(a,b);
    auto end = std::chrono::steady_clock::now();
    cout << "Return value: " << k << endl << "Digits in dividend: " << digits1 << endl;
    cout << "Digits in divisor: " << b.get_data().size() << endl;
    cout << "Runtime: " << std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count();
    cout << " ms" << endl << endl;
}
