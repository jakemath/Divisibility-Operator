 /*
 main.cpp
 Created by Jake Mathai on 2/4/2019.
 Copyright © 2019 Jake Mathai. All rights reserved.
 */

#include "../header/bigint.h"

int main(int argc, char* argv[]) {
    unsigned long long dividend_size = atoi(argv[1]), divisor_size = atoi(argv[2]);
    cout << "Generating operands..." << endl << endl;
    if (dividend_size < divisor_size) {
        cout << "Dividend size must be >= divisor size" << endl;
        exit(1);
    }
    else if (dividend_size == divisor_size)
        dividend_size = 1;
    else
        dividend_size -= divisor_size;
    bigint a(dividend_size, 1), b;
    short odds[4] = {7,9,3,1};
    if (divisor_size == 1) {
        srand(time(0));
        b.digits.push_back(odds[rand() % 2]);
    }
    else
        b = bigint(divisor_size, 1);
    if (b.digits.front() % 2 == 0) {
        srand(time(0));
        if (b.digits.size() > 1)
            b.digits.front() = odds[rand() % 4];
        else if (b.digits.size() == 1 && b.digits.front() != 2)
            b.digits.front() = odds[rand() % 3];
    }
    if (b.digits.front() == 5 && b.digits.size() > 1)
        b.digits.front() = odds[rand() % 4];
    else if (b.digits.front() == 1 && b.digits.size() == 1)     // If divisor is 1
        b.digits.front() = odds[rand() % 3];
    a = a * b;
    dividend_size = a.digits.size();
    cout << "Computing divisibility..." << endl << endl;
    bool divisible;
    auto start = std::chrono::steady_clock::now();
    divisible = div(a,b);
    auto end = std::chrono::steady_clock::now();
    cout << "A | B = " << (divisible ? "True" : "False") << "\nDIVIDEND SIZE = " << dividend_size
         << "\nDIVISOR SIZE = " << b.digits.size() << "\nRUNTIME = "
         << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << endl;
}
