#!/bin/bash
name=Game
echo -e '...:::# Uruchamiam '$name'.cpp #:::...'
echo

g++-8 -w -std=c++11 -o $name $name.cpp -lncurses

# Tu wstawić, że jeśli się nie skompiluje to nie uruchamiać programu
# Potrzebuję: Jaki błąd wysyła kompilator
rc=$?  # Store exit code for later use
if [ $rc -ne 0 ]; then  # $rc not equal to zero
    echo "...:::# Błąd kompilacji #:::..."
else
./$name
fi
