#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<string.h>
#include"include/load_koppae.h"
static char *msg;
static void init()
{
    int i;
    msg = malloc(MAX_MPI_MSG);
    //child_recv_msg = malloc(4*sizeof(char *));
}
static void deinit()
{
    int i;
    free(msg);
}
    
void load_parent()
{
    init();
    int i;
    //MPI_Request request;
    MPI_Status status;

    //debugger();
    strcpy(msg, "-a");
    MPI_Bcast(msg, MAX_MPI_MSG, MPI_CHAR, 0, comm);
    /*
    for(i=0; i<4; i++)
    {
        MPI_Irecv(child_recv_msg, MAX_MPI_MSG, MPI_CHAR, i, i, \
            comm, &request[i]);
    }
    */


    //debugger();
    //simulate

    /*
    int work = 400;
    int recv_check[i];
    strcpy(test_msg, "-c50");
    while(work>0)
    {
        for(i=0; i<4; i++)
        {     
            MPI_Test(&request[i], &recv_check[i], &status[i]); 
            if(recv_check[i])
            {
                work -= 50;
                MPI_Send(child_send_msg[i], MAX_MPI_MSG, MPI_CHAR, i, \
                    i, comm);
                MPI_Irecv(child_recv_msg[i], MAX_MPI_MSG, MPI_CHAR, i, \
                    i, comm, &request[i]);
            }
        }
    }
    */
    int work = 400;
    int child_rank;
    int child_tag;
    while(work>0)
    {
        MPI_Recv(msg, MAX_MPI_MSG, MPI_CHAR, MPI_ANY_SOURCE, \
            MPI_ANY_TAG, comm, &status);
        printf("[rid: %d] Recieved message: %s\n", rank, msg);
        child_rank = status.MPI_SOURCE;
        child_tag = status.MPI_TAG;
        strcpy(msg, "-c50");
        work -= 50;
        MPI_Send(msg, MAX_MPI_MSG, MPI_CHAR, child_rank, child_rank, comm);
    }
    for(i=0; i<4; i++)
    {
        MPI_Recv(msg, MAX_MPI_MSG, MPI_CHAR, MPI_ANY_SOURCE, \
            MPI_ANY_TAG, comm, &status);
        printf("[rid: %d] Recieved message: %s\n", rank, msg);
        child_rank = status.MPI_SOURCE;
        child_tag = status.MPI_TAG;
        strcpy(msg, "-e");
        MPI_Send(msg, MAX_MPI_MSG, MPI_CHAR, child_rank, child_rank, comm);
    }
    deinit();
}
