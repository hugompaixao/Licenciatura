#!/bin/bash

begin=0
	
while [ $begin -le $2 ]
do
	result=$(($1 * begin))
	echo "$1 x $begin = $result"
	begin=$((begin+1))
done
		
