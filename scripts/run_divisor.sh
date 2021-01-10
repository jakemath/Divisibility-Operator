#!/bin/bash
cd ..
rm logs/divisor_log.txt
DIVISOR_UPPER=$1
COMPILE=$2
if [[ "$COMPILE" == "true" ]]
then
    g++ -std=c++2a main/main_divisor.cpp header/bigint.h module/bigint.cpp
fi
./a.out $DIVISOR_UPPER >> logs/divisor_log.txt
