#!/bin/bash

for N in {1..1000}
do 
    ruby client.rb $((($N % 5) + 1)) & 
    echo $N
done
wait