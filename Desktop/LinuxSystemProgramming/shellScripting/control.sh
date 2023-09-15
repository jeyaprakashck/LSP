#!/bin/sh
#echo "Enter password"

#read str1

#while [ $str1 != "jeya" ]
#do 
#	echo "Entered password is wrong"
#	read str1
#done

#echo "Authendication is successful"


#echo $PWD
#cd /home/km/Desktop
#echo $PWD


#if conditions

#if [ -w abc.txt ] ; then
#	echo "abc.txt has write permission"
#fi


#for var1 in 0 1 2 3 4 5
#do 
#	echo \$var1 : $var1
#done

#for i in *
#do
#	if grep -rq abc.txt $i
#	then 
#		echo $i
#	fi
#	echo \$var1 : $i
#done

#for a in $(ls */ -d)
#do
#	echo $a
#done

counter(){
    for file in "$1"/* 
    do 
    if [ -d "$file" ]
    then 
            echo "$file"
            counter "$file"
    fi
    done
}

counter "$1"

i=1
k=5
while [ $k -ge $i ]
do
	#echo $i
	i=$(expr $i + 1)
done



