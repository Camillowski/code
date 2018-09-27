#!/bin/bash


#Variables
file=./temp.dat

#loop to read data from tail every 5 sec and write it to file
while[1 -ne 0]
do
	tail -n 1 /dev/ttyUSB0 >>$file
	echo -e '\n' >>$file
	sleep 5
done
