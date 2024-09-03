#!/bin/bash

echo "Enter number: "
	read num

fatorial=1

while [ $num -gt 1 ]
do
  fatorial=$((fatorial * num)) 
  num=$((num - 1))      
done
	
echo $fatorial
