#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
	int myrank, nprocs, len;
        char nome[10];

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Get_processor_name(nome, &len );

		printf("%s   -   Hello from processor %d of %d\n", nome, myrank, nprocs);

	MPI_Finalize();
	return 0;
}
