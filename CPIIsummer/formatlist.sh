#!/bin/bash
i=1
print=""

while read -ra line;
do
    for word in "${line[@]}";
    do
        if [ $i -ne 20 ] && [ $i -ne 21 ]
        then
            print="$print$word,"
            let i=$i+1 
        elif [ $i -eq 20 ]
        then
            print="$print$word"
            let i=$i+1
        else
            let i=1
            echo "$print" >> outputformat.txt
            print=""
        fi
    done;
done < N20.txt