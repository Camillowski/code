#!/bin/bash

MAKEFILE=Test.mak
DIR=~/Documents/Programowanie

make -f $DIR/make/$MAKEFILE $1

# name=Program
# echo -e '...:::# Uruchamiam '$name'.cpp #:::...'
# echo

# g++ -w -std=c++11 -o $name $name.cpp 

# # Ty wstawić, że jeśli się nie skompiluje to nie uruchamiać programu
# # Potrzebuję: Jaki błąd wysyła kompilator
# rc=$?  # Store exit code for later use
# if [ $rc -ne 0 ]; then  # $rc not equal to zero
    # echo "...:::# Błąd kompilacji #:::..."
# else
# ./$name #$1 $2 #$1 and $2 are for adding dditional parameter.
# fi
