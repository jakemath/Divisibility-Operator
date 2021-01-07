 /*
 main.cpp
 Created by Jake Mathai on 2/4/2019.
 Copyright © 2019 Jake Mathai. All rights reserved.
 */

#include "../header/bigint.h"

int main (int argc, char* argv[])
{
    unsigned long long dividend_upper = atoi(argv[1]), dividend_size;
    bigint b(10, true);
    short odds[4] = {7,9,3,1};
    if (b.digits.front() % 2 == 0) {
        srand(time(0));
        if (b.digits.size() > 1)
            b.digits().front() = odds[rand() % 4];
        else if (b.digits.size() == 1 && b.digits.front() != 2)
            b.digits().front() = odds[rand() % 3];
    }
    if (b.digits.front() == 5 && b.digits.size() > 1)
        b.digits().front() = odds[rand() % 4];
    else if (b.digits.front() == 1 && b.digits.size() == 1)     // If divisor is 1
        b.digits().front() = odds[rand() % 3];
    for (unsigned long long n = 11; n <= dividend_upper; ++n) {
        bigint a(n - b.digits.size(), true);
        a = a * b;
        dividend_size = a.digits.size();
        bool divisible;
        auto start = std::chrono::steady_clock::now();
        divisible = div(a,b);
        auto end = std::chrono::steady_clock::now();
        cout << divisible << " " << dividend_size << " " << b.digits.size() << " " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
    }
}
