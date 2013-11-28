#!/bin/bash

run_test=(
"/usr/bin/ssh -p22222 root@192.168.1.11 bash /koppae01/alone/diff_script.sh"
)


for cmd in "${run_test[@]}"; do {
  #echo "Process \"$cmd\" started";
  $cmd & pid=$!
  PID_LIST+=" $pid";
} done

trap "kill $PID_LIST" SIGINT

#echo "Parallel processes have started";

wait $PID_LIST

echo
#echo "All processes have completed";
