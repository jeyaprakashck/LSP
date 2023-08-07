fun()
{
	echo "inside the function"
	echo $1 $2
}

echo "starting point"
set -a
var1=$1

fun $var1



echo "function program ends here"

echo "exporting var1"

./export.sh
