#!/bin/sh

echo "enter two inputs"

read var1
read var2

echo $var1
echo $var2

if [ $var1 -gt  $var2 ]
then
	echo "equal"
fi
