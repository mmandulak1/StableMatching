#!/bin/bash
if [[ $2 -lt 4 ]]
then
    echo "Parameters missing (Tests, N)"
else
    for i in $(seq 4 $2)
    do
        ./repeatrun.sh $1 $i
    done
fi
