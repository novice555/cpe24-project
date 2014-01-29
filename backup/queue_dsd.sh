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

pid=`cat pid`
isrun=`ps -Al | awk -F' ' '{print $4}' | grep ^$pid$`
#echo $isrun
#echo $$
if [ -n "$isrun" ]
then
    echo $1 >> myqueue
else
    echo $$ > pid
    echo $1 > myqueue
    run=`head -n1 myqueue`
    filename=`echo $run | awk -F' ' '{print $5}'`
    outfile=`echo $run | awk -F' ' '{print $6}'`
    while [ -n "$run" ]
    do
        echo $run
        tail -n+2 myqueue > myqueue.tmp
        cat myqueue.tmp > myqueue
        rm myqueue.tmp
        #$run
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
        filename=`echo $run | awk -F' ' '{print $5}'`
        outfile=`echo $run | awk -F' ' '{print $6}'`
    done
fi
