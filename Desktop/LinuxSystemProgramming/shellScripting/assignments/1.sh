#Write shell script that will add two nos, which are supplied as command line argument, and if this two nos are not given show error and its usage

echo "This shell script will add two nos, which are supplied as command line argument, and if this two nos are not given show error and its usage"

echo "enter two numbers"

var1=$1
var2=$2
echo $#
if [ $# -ne 2 ]
then
	echo "Error : enter two number to add"
	exit 1
fi

echo $(expr $var1 + $var2)

