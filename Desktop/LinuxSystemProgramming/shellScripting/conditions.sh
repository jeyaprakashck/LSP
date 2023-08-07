#!/bin/sh

echo "Enter two numbers"

read var1
read var2

if [ $var1 -eq $var2 ]
then 
	echo "Numbers are equals"
else
	echo "Numbers are not equals"
fi
