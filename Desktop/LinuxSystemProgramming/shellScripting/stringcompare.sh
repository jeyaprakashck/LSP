#!/bin/sh

echo "Enter two strings"
read str1
read str2

if [ $str1 != $str2 ]
then
	echo "Equal"

else
	echo "Not equal"
fi
