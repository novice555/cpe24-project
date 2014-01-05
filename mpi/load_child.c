#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<string.h>
#include"include/load_koppae.h"
static char *msg;
static void init()
{
    msg = malloc(MAX_MPI_MSG);
}
static void deinit()
{
    free(msg);
}
void load_child()
{
    init();
    MPI_Status child_status;

    MPI_Bcast(msg, MAX_MPI_MSG, MPI_CHAR, 0, comm);
    printf("[rid: %d] Recieved MPI_Bcast: %s\n", rank, msg);
    printf("[rid: %d] Working old style.\n", rank);

    //simulate work
    int i, sum = 1;
    for(i=1; i<1000000000; i++)
        sum *= i;
    //end sumulate work

    printf("[rid: %d] Finishing old style.\n", rank);
    strcpy(msg, "-b");
    MPI_Send(msg, MAX_MPI_MSG, MPI_CHAR, 0, rank, comm);
    MPI_Recv(msg, MAX_MPI_MSG, MPI_CHAR, 0, rank, comm, &child_status);
    printf("[rid: %d] Recieved message: %s\n", rank, msg);
    
    int round = 0;
    char tmp[] = "-d";
    while(strcmp(msg, "-e"))
    {
    //simulate work
        round++;
        printf("[rid: %d] Working new style. Round %d\n", rank, round);
        char *str = &msg[2];
        int loop = atoi(str);
        for(i=1; i<loop*1000000; i++)
            sum *= i;
        //end simulate work
        printf("[rid: %d] Finishing new style.\n", rank);
        strcpy(msg, tmp);
        MPI_Send(msg, MAX_MPI_MSG, MPI_CHAR, 0, rank, comm);
        MPI_Recv(msg, MAX_MPI_MSG, MPI_CHAR, 0, rank, comm, &child_status);
        //MPI_Sendrecv_replace(msg, MAX_MPI_MSG, MPI_CHAR, 0, \
            rank, 0, 0, comm, &child_status);
        printf("[rid: %d] Recieved message: %s\n", rank, msg);
    }    
    printf("[rid: %d] Finishing Work. Terminate.\n", rank);
    deinit();
}
   
