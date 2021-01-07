 /*
 main.cpp
 Created by Jake Mathai on 2/4/2019.
 Copyright © 2019 Jake Mathai. All rights reserved.
 */

#include "../header/bigint.h"

int main (int argc, char* argv[])
{
    unsigned long long dividend_size = atoi(argv[1]), m = 2;
    std::default_random_engine generator;
    for (; m <= dividend_size; ++m) {
        bigint b(m, true);
        short odds[4] = {7,9,3,1};
        if (b.digits.front() % 2 == 0) {
            if (b.digits.size() > 1) {
                std::uniform_int_distribution<int> uniform(0, 3);
                b.digits().front() = odds[uniform(generator)];
            }
            else if (b.digits.size() == 1 && b.digits.front() != 2) {
                std::uniform_int_distribution<int> uniform(0, 2);
                b.digits.front() = odds[uniform(generator)];
            }
        }
        if (b.digits.front() == 5 && b.digits.size() > 1) {
            std::uniform_int_distribution<int> uniform(0, 3);
            b.digits.front() = odds[uniform(generator)];
        }
        else if (b.digits.front() == 1 && b.digits.size() == 1) {
            std::uniform_int_distribution<int> uniform(0, 2);
            b.digits.front() = odds[uniform(generator)];
        }
        bigint a(dividend_size - m, true);
        a = a * b;
        std::uniform_int_distribution<int> uniform(2, 9);
        while (a.digits.size() < dividend_size)
            a = a * uniform(generator);
        dividend_size = a.digits.size();
        bool divisible;
        auto start = std::chrono::steady_clock::now();
        divisible = div(a, b);
        auto end = std::chrono::steady_clock::now();
        cout << divisible << " " << dividend_size << " " << m << " " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
    }
}
