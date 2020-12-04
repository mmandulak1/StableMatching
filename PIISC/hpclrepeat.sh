#!/bin/bash
if [[ $2 -lt 4 ]]
then
    echo "Parameters missing (Tests, N)"
else
    for i in $(seq $2 $3)
    do
        ./repeatrun.sh $1 $i
    done
fi
