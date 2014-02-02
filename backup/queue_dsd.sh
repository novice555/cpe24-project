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
#path_result="/var/www/cake/app/result"
inpath="/koppae/working/uploads"
outpath="/koppae/working/result"
samepath="/koppae/working/same"
outfile="/tmp/output.txt"
infile="/koppae/data/input.txt"

pid=`cat pid`
isrun=`ps -Al | awk -F' ' '{print $4}' | grep ^$pid$`
#echo $isrun
#echo $$
if [ -n "$isrun" ]
then
    echo "$@"
else
    echo $$ > pid
    run=($(mysql <<< "SELECT * FROM \`queues\` ORDER BY \`id\` ASC LIMIT 1" | tail -n1))
    #run=`head -n1 myqueue`
    while [ -n "$run" ]
    do
        echo ${run[@]}
	    #init argument
        #read -a runarray <<< "$run"
        #filename="${runarray[0]}"
        #types="${runarray[@]:1}"
        filename="${run[2]}"
        types="${run[@]:3}"
	    echo $filename
	    echo $types
	    #dequeue
        $(mysql <<< "DELETE FROM \`queues\` ORDER BY \`id\` ASC limit 1")
        #tail -n+2 myqueue > myqueue.tmp
        #cat myqueue.tmp > myqueue
        #rm myqueue.tmp
	    #copy to child
	    cp $inpath/$filename.upload /koppae/data/input.txt
	    cp $inpath/$filename.upload /koppae/child/01/input.txt
	    cp $inpath/$filename.upload /koppae/child/02/input.txt
	    cp $inpath/$filename.upload /koppae/child/03/input.txt
	    cp $inpath/$filename.upload /koppae/child/04/input.txt
	    #run
	    echo "mpirun -hostfile /jo/gdis.txt /jo/dsd $infile $outfile $types"
        rm -f $outfile
        mysql <<< "UPDATE \`distributed\`.\`diff\` SET \`status\` = 2 WHERE \`diff\`.\`id\` = ${run[1]}"
        mpirun -hostfile /jo/gdis.txt /jo/dsd $infile $outfile $types
        result=`cat $outfile`
        if [ -n "$result" ]
        then
            filesame=`cat $outfile | head -n1`
            percent=`cat $outfile | head -n2 | tail -n1`
            cat $outfile | tail -n+3 > $outpath/$filename.result
            #fileresult=`< /dev/urandom tr -dc A-Za-z0-9 | head -c10`
            #aout=$($outfile | tail -n+4)
            #if [ -n "$aout" ]
            #then
            #    cat $outfile | tail -n+3 > $outpath/$filename.result
            #else
	        #    cp $inpath/$filename.upload $outpath/$filename.result
            #fi
            chown www-data $outpath/$filename.result
            echo "UPDATE \`distributed\`.\`diff\` SET \`status\` = 0, " > update.sql
            echo "\`samename\` = '$filesame', " >> update.sql
            echo "\`modified\` = NOW(), \`percent\` = '$percent' " >> update.sql
            echo "WHERE \`diff\`.\`filename\` = '$filename';" >> update.sql
            mysql < update.sql
            cp $filesame $samepath/$filename.same
        fi
        run=($(mysql <<< "SELECT * FROM \`queues\` ORDER BY \`id\` ASC LIMIT 1" | tail -n1))
    done
fi


            #echo "UPDATE \`distributed\`.\`diff\` SET \`filesame\` = '$filesame', " > update.sql
            #echo "\`finished\` = '1', \`result\` = '$path_result/$fileresult', " >> update.sql
            #echo "\`modified\` = NOW(), \`percent\` = '$percent' " >> update.sql
            #echo "WHERE \`diff\`.\`filename\` = '$filename';" >> update.sql
            #mysql < update.sql
