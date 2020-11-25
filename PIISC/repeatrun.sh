#!/bin/bash
#for i in $(seq 1 $1)
#do
 #   ./RDM $2 > prefList.txt
#    ./PIISC >> ./RunResults/results_$2.txt
#    echo "done $i"
#done
g++ -o PIISC PIISC.cpp

SECONDS=0
echo "PII-SC Started for Random Inputs of size n=$2, $1 times"
echo "PII-SC Started for Random Inputs of size n=$2, $1 times" >> HPCLruntimes.txt
#./PIISC $1 >> ./RunResults/results_$2.txt
./PIISC $1 $2 >> ./HPCLtests/results_$2.txt
let minutes=$SECONDS/60
let secondsAfter=$SECONDS-$minutes*60
echo "PII-SC Completed $1 trials after $minutes minutes and $secondsAfter seconds"
echo "PII-SC Completed $1 trials after $minutes minutes and $secondsAfter seconds" >> HPCLruntimes.txt
