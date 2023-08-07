#2. Write Script to find out biggest number from given three nos. Nos are supplied as command line arguments. Print error if sufficient arguments are not supplied.


if [ $# -ne 3 ]
then
	echo "Error : please enter three numbers"
	exit 1
fi

if [ $1 -gt $2 ]
then
	if [ $1 -gt $3 ]
	then
		echo "The biggest no is $1"
		exit 
	fi
fi
if [ $2 -gt $3 ]
then
	echo "The biggest no is $2"
else
	echo "The biggest no is $3"
fi

echo " done"
