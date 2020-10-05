#!/bin/bash

time=4
destinations=("www.ufrj.br" "www.ucla.edu" "www.phil.cam.uk" "www.adelaide.edu.au");
testsPerDestination=2

for dest in "${destinations[@]}"; do
    filename=time-$time-dest-$dest.txt
    > $filename

    for _ in {1..$testsPerDestination}; do
        traceroute $dest -4 >> $filename;
    done;
done;
