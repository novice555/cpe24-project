#!/bin/bash
cd /koppae
#init
if [ ! -f pid ]
then
    echo "-1" > pid
fi
if [ ! -f myqueue ]
then
    echo -n "" > myqueue
fi
path_result="/var/www/cake/app/result"
outfile="/tmp/output.txt"
infile="/koppae/data/input.txt"

pid=`cat pid`
isrun=`ps -Al | awk -F' ' '{print $4}' | grep ^$pid$`
#echo $isrun
#echo $$
if [ -n "$isrun" ]
then
    echo "$@" >> myqueue
else
    echo $$ > pid
    echo $@ >> myqueue
    run=`head -n1 myqueue`
    while [ -n "$run" ]
    do
        echo $run
	#init argument
        read -a runarray <<< "$run"
        filename="${runarray[0]}"
        types="${runarray[@]:1}"
	echo $filename
	echo $types
	#dequeue
        tail -n+2 myqueue > myqueue.tmp
        cat myqueue.tmp > myqueue
        rm myqueue.tmp
	#copy to child
	cp $filename /koppae/data/input.txt
	cp $filename /koppae/child/01/input.txt
	cp $filename /koppae/child/02/input.txt
	cp $filename /koppae/child/03/input.txt
	cp $filename /koppae/child/04/input.txt
	#run
	echo "mpirun -hostfile /jo/gdis.txt /jo/dsd $infile $outfile $types"
	mpirun -hostfile /jo/gdis.txt /jo/dsd $infile $outfile $types
        result=`cat $outfile`
        if [ -n "$result" ]
        then
            filesame=`cat $outfile | head -n1`
            percent=`cat $outfile | head -n2 | tail -n1`
            fileresult=`< /dev/urandom tr -dc A-Za-z0-9 | head -c10`
            cat $outfile | tail -n+3 > $path_result/$fileresult
            chown www-data $path_result/$fileresult
            echo "UPDATE \`distributed\`.\`diff\` SET \`filesame\` = '$filesame', " > update.sql
            echo "\`finished\` = '1', \`result\` = '$path_result/$fileresult', " >> update.sql
            echo "\`modified\` = NOW(), \`percent\` = '$percent' " >> update.sql
            echo "WHERE \`diff\`.\`filename\` = '$filename';" >> update.sql
            mysql < update.sql
        fi
        run=`head -n1 myqueue`
    done
fi
