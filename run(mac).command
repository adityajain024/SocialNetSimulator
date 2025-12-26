#!/bin/bash
cd "$(dirname "$0")"
clear
echo "Compiling socialnet.cpp..."
g++ socialnet.cpp -std=c++17 -O2 -Wall -o socialnet.out

if [ $? -ne 0 ]; then
    echo
    echo "*** compile failed ***"
    read -n 1 -s -r -p "Press any key to close"
    exit 1
fi

echo
echo "Running..."
echo "------------------------------------"
./socialnet.out
echo "------------------------------------"
echo
echo "Terminal will stay open for more commands."
$SHELL
