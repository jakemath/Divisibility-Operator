#!/usr/bin/env bash
rm dividend_log.txt
DIVIDEND_UPPER=$1
COMPILE=$2
if [[ "$COMPILE" == "true" ]]
then
    g++ -std=c++2a ../main/main_dividend.cpp ../header/bigint.h ../module/bigint.cpp
fi
./a.out ${DIVIDEND_UPPER} >> ../logs/dividend_log.txt
