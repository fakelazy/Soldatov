#include <stdio.h>
#include "mpi.h"
using namespace std;
int main(int argc, char* argv[]) {
	MPI_Init(&argc, &argv);
	int rank, n, i, message;
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank == 0) {
		cout << "Hello from process " << rank << "\n";
		MPI_Recv(&message, 1, MPI_INT, n - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		cout << "Process " << rank << " got message " << message << "\n";
	} else if (rank == 1) {
		message = 1;
		cout << "Process " << rank << " started game with message " << message << "\n";
		MPI_Send(&message , 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
	} else {
		MPI_Recv(&message, 1, MPI_INT, rank - 1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		cout << "Process " << rank << " got message " << message << "\n";
		
		message += 1;

		if (rank == n - 1) {
			MPI_Send(&message, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		} else {
			MPI_Send(&message, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();
	return 0;
}