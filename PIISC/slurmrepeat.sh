#!/bin/bash
if [[ $2 -lt 4 ]]
then
    echo "Parameters missing (Tests, Nmin, Nmax)"
else
    let "numruns=$1"
    for i in $(seq $2 $3)
    do
	let "x=$i"
	export x
	export numruns
        cat slurm_repeat_template.sh | sbatch --ntasks=1 
    done
fi


