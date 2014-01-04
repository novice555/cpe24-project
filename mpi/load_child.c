#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<string.h>
#include"include/load_koppae.h"
void load_child()
{
    char msg[MAX_MPI_MSG];
    char *msg_ptr = msg;
    MPI_Status child_status;

    MPI_Bcast(msg_ptr, MAX_MPI_MSG, MPI_CHAR, 0, comm);
    printf("[rid: %d] Recieved MPI_Bcast: %s\n", rank, msg);
    printf("[rid: %d] Working old style.\n", rank);

    //simulate work
    int i, sum = 1;
    for(i=1; i<10000000; i++)
        sum *= i;
    //end sumulate work

    printf("[rid: %d] Finishing old style.\n", rank);
    strcpy(msg, "-b");
    msg_ptr = msg;
    MPI_Sendrecv_replace(msg, MAX_MPI_MSG, MPI_CHAR, 0, MPI_ANY_TAG, \
        0, MPI_ANY_TAG, comm, &child_status);
    printf("[rid: %d] Recieved message: %s\n", rank, msg);
    
    int round = 0;
    while(strcmp(msg, "-e"))
    {
    //simulate work
        round++;
        printf("[rid: %d] Working new style. Round %d\n", rank, round);
        char *str = &msg[2];
        int loop = atoi(str);
        for(i=1; i<loop*10000; i++)
            sum *= i;
        //end simulate work
        printf("[rid: %d] Finishing new style.\n", rank);
        MPI_Sendrecv_replace(msg_ptr, MAX_MPI_MSG, MPI_CHAR, 0, MPI_ANY_TAG, \
            0, MPI_ANY_TAG, comm, &child_status);
        printf("[rid: %d] Recieved message: %s\n", rank, msg);
    }    
    printf("[rid: %d] Finishing Work. Terminate.\n", rank);
    
}
   
