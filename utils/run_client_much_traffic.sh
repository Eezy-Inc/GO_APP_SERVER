#!/bin/bash

for N in {1..20}
do 
    ruby client.rb $((($N % 5) + 1)) & 
done
wait