#!/bin/bash
for ((i=1; i<5; i++))
do
	ssh -p22222 root@192.168.1.1$i "echo \"find /koppae0$i/child0$i -name \*.txt -exec diff /koppae0$i/test.input {} > /dev/null  \;\" > /koppae0$i/diff_script.sh"
done

