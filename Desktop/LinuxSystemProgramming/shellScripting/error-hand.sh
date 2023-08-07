#!/bin/sh

ping -c 1 www.google.com > /dev/null

if [ $? -eq 0 ]
then 
	echo "Internet is working"
else
	echo "Internet is not working"
	exit 4
fi



lss

echo "ls command status : $?"
