#!/bin/bash

for i in *.jpeg
do
echo "Processing image $i ..."
convert -thumbnail 200 $i thumb.$i
done
