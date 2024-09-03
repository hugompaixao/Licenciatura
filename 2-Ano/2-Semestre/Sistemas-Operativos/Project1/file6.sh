#!/bin/bash

echo "Introduza o Ano"
	read year
	
check1=$(($year % 4))
check2=$(($year % 100))
check3=$(($year % 400))
if [ $check1 -eq 0 ] || [ $check2 -eq 0 ] || [ $check3 -eq 0 ]; then
	echo "Neste ano Feverreiro tem 29 dias"
else
	echo "Neste ano Fevereiro tem 28 dias"
fi



