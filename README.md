# Divisibility-Operator

An implementation and driver program for a O(n) divisibility operator inspired by General Divisibility Criteria (https://arxiv.org/pdf/1401.5486.pdf). The operator computes divisibility of large positive integers by other large positive (mostly odd) integers.

Numbers are represented digit-wise in reverse order in a linked list to enable arithmetic with numbers with an arbitrary amount of digits. The algorithm iteratively reduces the dividend by one digit from the least significant side using number theoretic divisibility rules that can be computed for any odd number ending in 1, 3, 7, or 9. The divisibility rule for a number is computed by finding the first multiple of the number that ends in a 1 or a 9. If it ends in a 1 --> truncate the ones digit and the rule is to subtract the remaining leading truncated number. If it ends in a 9 --> truncate the ones digit, increment the truncated number, and the rule is to add the remaining leading truncated number. Numbers that end in a 1 or 9, therefore, require no further computations for the rule. Numbers that end in 3 or 7 may simply be multiplied by 3 since that multiple will necessarily end in 9 or 1, respectively.

Examples: 

          7 --> 21 --> rule = -2
          13 --> 39 --> rule = 4
          11 --> rule = -1
          19 --> rule = 2

The rule is multiplied by the ones digit of the dividend and the product is added to the dividend with its ones digit truncated.This process can be iterated until the dividend becomes small enough to clearly recognize divisibility. If the dividend is transformed to an obvious multiple of the divisor or 0, then the dividend is divisible by the divisor. Otherwise, it is not. 

Examples: 

          div (826, 7): 826 --> 82 + (-2 * 6) = 70 = 10 * 7, therefore 826 is divisible by 7.
          div (19151, 11): 19151 --> 1915 + (-1 * 1) = 1914 --> 191 + (-1 * 4) = 187 --> 18 + (-1 * 7) = 11 = 1 * 11, therefore 19151 is divisible by 11.
          div (50661,13): 50661 --> 5066 + (4 * 1) = 5070 --> 507 + (4 * 0) = 507 --> 50 + (4 * 7) = 78 = 6 * 13, therefore 50661 is divisible by 13.
       
One can easily see this algorithm is necessarily O(n) and pairs nicely with a linked list implementation, where we can pop digits in constant time. The program incorporates elementary arithmetic functions and specialized multiplication functions for different contexts. To save runtime cost from clearing digits, a number that becomes 0 after an operation is marked with a 0 in the most significant digit.

To run the driver program:

          >>> g++ bigint.h bigint.cpp main.cpp
          >>> ./a.out <dividend size in digits> <divisor>

The divisor input can be 2, 5, or any number greater than 5 ending in a 1, 3, 7, or 9. This is to accomodate use of "probably prime" numbers" - i.e. prime numbers only end in 1, 3, 7, or 9, so computing divisibility by numbers ending in 5 or an even number (besides 2) is trivial when determining primality.
          
The program will generate a random dividend of the first argument, then multiply it by the second argument. It then will print the dividend (which is pretty cool to see when you input a 1,000,000+ digit number), then run the divisibility operator on the two numbers and print the return value. We know the operator is working when it returns a value of 1, divisible, as expected.
The last output is the runtime in milliseconds for the computation.
