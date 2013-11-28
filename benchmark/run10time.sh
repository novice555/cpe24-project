#!/bin/bash
for ((i=1; i<11; i++))
do
/usr/bin/time -v ./parallel_commands.sh run_seq &> test_diff_seq.v$i
sleep 600
/usr/bin/time -v ./parallel_commands.sh run_parallel &> test_diff_parallel.v$i
sleep 600
done
