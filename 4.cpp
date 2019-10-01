#include <iostream>
#include "mpi.h"
using namespace std;
int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv); //запуск MPI
    int rank, n, i, message;
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &n);

	//int MPI_Comm_size (MPI_Comm students, int *size)Функция нахождения числа процессов выполняемой параллельной программы.

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    
	//int MPI_Comm_rank (MPI_Comm students, int *rank) Функция определения ранга процесса. comm - идентификатор группы

    if (rank == 0){
        cout << "Hello from process " << rank << "\n";
        for (i=1; i<n; i++){
            MPI_Recv(&message, 1, MPI_INT, MPI_ANY_SOURCE,MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            cout << "Hello from process " << message << endl;
        }
    }
else cout << rank << "Kyky" << endl;
    //else MPI_Send(&rank,1,MPI_INT,0,0,MPI_COMM_WORLD); //отправление нулевому процессу

    MPI_Finalize();
return 0;
}