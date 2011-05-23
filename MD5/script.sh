#!/bin/bash

declare -A massiv

while read y z; do
    
    while read x && [[ -n $x ]];do
	massiv[$x]="$y--$z"
    done
done <file1


while read  x y z; do
    if [[ ${massiv[$z]} != "$x--$y" ]]; then
	echo "Changed file: $z.Was: ${massiv[$z]}.Now: $x--$y"
	fi;
done <file2


#echo ${massiv['filename1']} ${massiv['filename2']}