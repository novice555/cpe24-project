#include<stdio.h>
#include<mpi.h>
#include"include/load_koppae.h"
int rank, np;
MPI_Comm comm;
void load_koppae(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &np);
    MPI_Comm_rank(comm, &rank);
    if(rank==0)
    {
        //printf("%d\n", rank);
        debugger();
        load_parent();
    }
    else
    {
        //printf("%d\n", rank);
        load_child();
    }
    MPI_Finalize();
}

