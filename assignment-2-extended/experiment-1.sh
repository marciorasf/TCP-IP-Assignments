#!/bin/bash

time=4
destinations=("www.ufrj.br" "www.ucla.edu" "www.phil.cam.uk" "www.adelaide.edu.au");
testsPerDestination=10

for dest in "${destinations[@]}"; do
    filename=time-$time-dest-$dest.txt
    > $filename

    for counter in $(seq 1 $testsPerDestination); do
        echo "Iteration $counter" >> $filename;
        echo "" >> $filename;
        traceroute $dest -4 >> $filename;
        echo "" >> $filename;
        echo "-----------------------------------------------------------------------" >> $filename;
        echo "" >> $filename;
    done;
done;
