#!/bin/bash
#SBATCH --job-name=PIISC
#SBATCH --exclude=hpcl1-1 

echo $x
echo
echo $numruns
echo
g++ -std=c++11 -o PIISC PIISC.cpp

SECONDS=0
echo "PII-SC Started for Random Inputs of size n=$x, $numruns times"
echo "PII-SC Started for Random Inputs of size n=$x, $numruns times" >> ./SlurmRuns/HPCLruntimes.txt
#./PIISC $1 >> ./RunResults/results_$2.txt
srun PIISC $numruns $x >> ./SlurmRuns/results_$x.txt
let minutes=$SECONDS/60
let secondsAfter=$SECONDS-$minutes*60
echo "PII-SC Completed $numruns trials for n=$x after $minutes minutes and $secondsAfter seconds"
echo "PII-SC Completed $numruns trials for n=$x after $minutes minutes and $secondsAfter seconds" >> ./SlurmRuns/HPCLruntimes.txt


