#!/bin/sh

IFS='._'

echo "Shell name : \$0 = $0"
echo "Shell 1st argument : \$1 = $1"
echo "Shell 2nd argument : \$2 = $2"
echo "Shell no of argument : \$# = $#"
echo "Shell PID no : \$$ = $$"
echo "List of all parameters : \$* = $*"
echo "List of all parameters : \$@ = $@"
