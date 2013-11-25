#include<stdio.h>
#include<stdlib.h>
#include"include/distribute.h"

static void make_script_parallel(char *path)
{
    FILE *run;
    if((run = fopen(path, "w"))==NULL)
    {   
        fprintf(stderr, "Cannot write file: %s\n", path);
        exit(1);
    }
    fprintf(run, "                                \n    \
        if [ ! -f \"$1\" ] || [ -z \"$1\" ]       \n    \
        then                                      \n    \
            echo \"Error. Filename incorrect.\"   \n    \
            exit 1                                \n    \
        fi                                        \n    \
                                                  \n    \
                                                  \n    \
        file=$1                                   \n    \
        while read cmd                            \n    \
        do {                                      \n    \
          echo \"Process \\\"$cmd\\\" started\";  \n    \
          $cmd & pid=$!                           \n    \
          PID_LIST+=\" $pid\";                    \n    \
        } done < $file                            \n    \
                                                  \n    \
        trap \"kill $PID_LIST\" SIGINT            \n    \
                                                  \n    \
        #echo \"Parallel processes have started\";\n    \
                                                  \n    \
        wait $PID_LIST                            \n    \
        ");
    fclose(run);                                     
}

int run_parallel(char *script_path)
{
    int sys;
    char strbuf[MAX_PATH] = "";
    int i;
    char *run_script = "/tmp/run_parallel.sh";

    if(system(NULL)==0)
    {
        fprintf(stderr, "Cannot run bash command. May be RAM are full?\n");
        exit(EXIT_FAILURE);
    }
    make_script_parallel(run_script);
    
    sprintf(strbuf, "bash  %s %s", run_script, script_path);
    printf("%s\n", strbuf);
//    rsync_open = popen(strbuf, "r");
    sys = system(strbuf);
    if(sys != 0)
        fprintf(stderr, "System Execute Error: Code %d.\n", sys);
//    while(fgets(buff, sizeof(buff), rsync_open)!=NULL)
//        printf("%s", buff);
    return 0;
}

