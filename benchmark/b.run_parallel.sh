#!/bin/bash

run_test=(
"ssh -p22222 root@192.168.1.11 bash /koppae01/child01/diff_script.sh"
"ssh -p22222 root@192.168.1.12 bash /koppae02/child02/diff_script.sh"
"ssh -p22222 root@192.168.1.13 bash /koppae03/child03/diff_script.sh"
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
