#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include"include/distribute.h"
static void *rsync_function(void *arg)
{
    char *command = (char *) arg;
    FILE *rsync_open;
    char buff[1024];
    
    printf("%s", command);
    if((rsync_open = popen(command, "r"))==NULL)
    {
        fprintf(stderr, "System execution error: Cannot run command \"%s\".\n", command);
        exit(1);
    }
    while(fgets(buff, sizeof(buff), rsync_open)!=NULL)
    {
        printf("%s", buff);
    }
    pclose(rsync_open);
    return 0;
}

void rsync_copy(char cmd[][MAX_COMMAND], int n)
{
    if(system(NULL)==0)
    {
        fprintf(stderr, "System execution error: Cannot execute system command.\n");
        exit(1);
    }
    
    pthread_t thread_rsync[n];
    int pthread_create_check = 0;
    int i;
    
    for(i=0; i<n; i++)
    {
        pthread_create_check += pthread_create(&thread_rsync[i], NULL, rsync_function, (void *) cmd[i]);
    }
    for(i=0; i<n; i++)
    {
        pthread_join(thread_rsync[i], NULL);
    }

 //   printf("%s\n", strbuf);
    if(pthread_create_check != 0)
    {
        fprintf(stderr, "System execution error: pthread_create error");
        exit(1);
    }
}

