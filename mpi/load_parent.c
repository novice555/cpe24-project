#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<string.h>
#include"include/load_koppae.h"
void load_parent()
{
    char msg[MAX_MPI_MSG];
    char *msg_ptr = msg;
    char child_msg[4][MAX_MPI_MSG];
    int i;
    MPI_Request request[4];
    MPI_Status status[i];

    strcpy(msg, "-a");
    MPI_Bcast(msg_ptr, MAX_MPI_MSG, MPI_CHAR, 0, comm);
    for(i=0; i<4; i++)
    {
        msg_ptr = child_msg[i];
        MPI_Irecv(msg_ptr, MAX_MPI_MSG, MPI_CHAR, i, MPI_ANY_TAG, \
            comm, &request[i]);
    }
    
    //simulate
    int work = 400;
    int recv_check[i];
    while(work)
    {
        for(i=0; i<4; i++)
        {     
            MPI_Test(&request[i], &recv_check[i], &status[i]); 
            if(recv_check[i])
            {
                strcpy(child_msg[i], "-c");
                strcat(child_msg[i], "50");
                work -= 50;
                MPI_Send(child_msg[i], MAX_MPI_MSG, MPI_CHAR, i, \
                    MPI_ANY_TAG, comm);
                MPI_Irecv(child_msg[i], MAX_MPI_MSG, MPI_CHAR, i, \
                    MPI_ANY_TAG, comm, &request[i]);
            }
        }
    }
}
