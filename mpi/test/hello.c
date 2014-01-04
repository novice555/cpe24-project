#include<string.h>
#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
    int rank, np;
    int i;
    char *msg;
    MPI_Status status;
    MPI_Comm comm = MPI_COMM_WORLD;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(comm, &np);
    MPI_Comm_rank(comm, &rank);
    msg = (char *) malloc(sizeof(25));
    
    if(rank==0)
    {
        for(i=1; i<np; i++)
        {
            MPI_Recv(msg, 25, MPI_CHAR, i, 0, comm, &status);
            printf("%s\n", msg);
        }
    }
    else
    {
        sprintf(msg, "Hello World from rank %d", rank);
        MPI_Send(msg, 25, MPI_CHAR, i, 0, comm);
    }
    MPI_Finalize();
}
