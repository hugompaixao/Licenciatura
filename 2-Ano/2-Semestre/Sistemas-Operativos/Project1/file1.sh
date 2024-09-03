#!/bin/bash

echo "Enter 1 to - List files with a user-defined extension"
echo "Enter 2 to - List directories whose size is greater than a user-defined dimension"
echo "Enter 3 to - List files whose date falls within a time interval defined by the user"
echo "Enter 4 to - List logins and user names of the sistem"
echo "Enter 5 to - List files that contain a user-given expression"
	read case
	
case $case in 

1)
	echo "Enter desired extension: "
		read extension
	ls *.$extension;;
	
2)
	echo "Enter desired size: "
		read num
	find -type d -size +$(($num))c;;

3)
	echo "Formato: AAAA-MM-DD"
	echo "Introduza data de:"
		read start
	echo "Introduza data ate:"
		read end
	find . -type f -newermt $start ! -newermt $end;;

4)
	while IFS=: read -r f1 f3; do
	echo "Login: $f3"			"Nome de Utilizador: $f1"
	done </etc/passwd;;
 
5)
	echo "Enter Expression:"
		read word
	grep -r $word;;
	
esac
