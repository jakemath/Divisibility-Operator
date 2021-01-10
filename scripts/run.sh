#!/bin/bash
cd source
DIVIDEND=$1
DIVISOR=$2
COMPILE=$3
if [[ "$COMPILE" == "true" ]]
then
    echo "COMPILING..."
    g++ -std=c++2a main/main.cpp header/bigint.h module/bigint.cpp
fi
./a.out $DIVIDEND $DIVISOR
