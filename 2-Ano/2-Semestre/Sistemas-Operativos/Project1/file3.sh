#!/bin/bash

echo "Extensão atual"
	read now
echo "Extensão desejada"
	read want
	
for f in *.$now; do
		mv -- "$f" "${f%.$now}.$want"
	done
