#!/bin/bash

if [ ! -f "$1" ] || [ -z "$1" ]
then
    echo "Error. Filename incorrect."
    exit 1
fi


file=$1
while read cmd
do {
  echo "Process \"$cmd\" started";
  $cmd & pid=$!
  PID_LIST+=" $pid";
} done < $file

trap "kill $PID_LIST" SIGINT

#echo "Parallel processes have started";

wait $PID_LIST

#echo "All processes have completed";

