/*
 main.cpp
 Created by Jake Mathai on 2/4/2019.
 Copyright © 2019 Jake Mathai. All rights reserved.
 */

#include "bigint.h"

int main (int argc, char* argv[])
{
    short o[4] = {3, 7, 9, 1};
    unsigned long long digits1 = atoi(argv[1]), digits2 = atoi(argv[2]);
    bigint b;
    if (digits2 == 0)
    {
        string in;
        cout << "Enter divisor (can be 2, 3, 5, or any greater positive integer ending in 1, 3, 7, or 9)" << endl;
        std::cin >> in;
        if (in == "1" || in[in.length() - 1] == '0' || (in[in.length() - 1] == '2' && in != "2") || in[in.length() - 1] == '4' || in[in.length() - 1] == '6' || in[in.length() - 1] == '8' || (in != "5" && in[in.length() - 1] == 5)) // Catch invalid inputs
        {
            cout << "Invalid input; exiting" << endl;
            exit(1);
        }
        else
            b = bigint(in);
    }
    else
        b = bigint(digits2, 1);
    bigint a(digits1, 1);
    srand(time(0));
    if ((b.get_data().front() % 2 == 0 && b.get_data().size() > 1) || (b.get_data().front() == 5 && b.get_data().size() > 1))    // If divisor is even or ends in a 5 and is not 5
        b.get_data().front() = o[rand() % 4];
    else if (b.get_data().front() == 1 && b.get_data().size() == 1)     // If divisor is 1
        b.get_data().front() = o[rand() % 3];
    a = a * b;
    digits1 = a.get_data().size();
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
