#include<stdio.h>
#include<mpi.h>
#include"include/load_koppae.h"
int rank, np;
MPI_Comm comm;
MPI_Comm comm2;
MPI_Group testgroup;

void load(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &np);
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_group(comm, &testgroup);
    MPI_Comm_create(comm, testgroup, &comm2);
    if(rank==0)
    {
        //printf("%d\n", rank);
        debugger();
        load_parent();
    }
    else
    {
        //printf("%d\n", rank);
        debugger();
        load_child();
    }
    MPI_Finalize();
}

