#!/bin/bash

echo "Enter files"
	read file1
	read file2

cat $file1 $file2 > file3
wc -l file3
