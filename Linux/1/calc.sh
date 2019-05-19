#!/bin/bash

echo -n "Enter first arg: "
read val_1

echo -n "Enter second arg: "
read val_2

echo -n "Read operation: "
read operator

case "$operator" in
	["+-*/"] )
	if (( $(echo "$val_2 == 0" | bc -l) )); then
		echo Error: division by zero!
		exit
	fi
	
	prec=$1
	if [ -z $1 ]; then
		prec=8
	fi

	result=$(echo "scale=$prec; $val_1$operator$val_2" | bc -l)
	echo Result: $result
	;;
	
	* )
	echo Error: wrong operation!
	;;
esac
