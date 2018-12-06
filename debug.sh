#!/bin/bash
DIR=~/Documents/Programowanie
DFLAGS="-g -std=c++11 -I $DIR/include"
g++ $DFLAGS -o ./debug/$1.o ./src/$1.cpp
#gdb ./debug/$1.o&& #q- if I want quiet
rm ./debug/$1.o