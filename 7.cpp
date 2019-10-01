#include <iostream>
#include <mpi.h>
using namespace std;
int main(int argc, char **argv)
{
	int rank, size, ibuf;
	MPI_Status status;
	float rbuf;
	MPI_Init(&argc, &argv);	//инициализация среды выполнения MPI-программы 
				//(число аргументов,указатель на массив символов)

	MPI_Comm_size(MPI_COMM_WORLD, &size);	//функция нахождения числа процессов выполняемой параллельной программы.
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	//функция определения ранга процесса. comm - идентификатор группы

	ibuf = rank;	//приравниваем ibuf к рангу процесса
	rbuf = 1.0 * rank;	

	if(rank==1) MPI_Send(&ibuf, 1, MPI_INT, 0, 5, MPI_COMM_WORLD);	//идентификатор процесса-получателя 5
	if(rank==2) MPI_Send(&rbuf, 1, MPI_FLOAT, 0, 5, MPI_COMM_WORLD);	//идентификатор процесса-получателя 5

	cout << "rank out of cycle= " << rank << endl;

	if(rank==0){
		MPI_Probe(MPI_ANY_SOURCE, 5, MPI_COMM_WORLD, &status);	
		//процесс 0 ждет сообщение от любого из процессов 1 и 2 с одним и тем же тегом
		//посылаемые этими процессами данные имеют разный тип
		//MPI_Probe сначала определяет, от кого именно поступило сообщение
		//после получения результатов от MPI_Probe в нужную переменную помещается сообщение
		//MPI_Recv принимает сообщение

		if(status.MPI_SOURCE == 1){	//status.MPI_SOURCE- источник принятого сообщения

			MPI_Recv(&ibuf, 1, MPI_INT, 1, 5, MPI_COMM_WORLD, &status);	//приходит сообщение с 1: if(rank==1)
			MPI_Recv(&rbuf, 1, MPI_FLOAT, 2, 5, MPI_COMM_WORLD, &status);	//приходит сообщение со 2: if(rank==2)

			cout << "rank cycle(1)= " << rank << endl;

			cout << "Process 0 recv " << ibuf << " from process 1, " << rbuf << " from process 2\n";
		}

		else if(status.MPI_SOURCE == 2){	//status.MPI_SOURCE- источник принятого сообщения

			MPI_Recv(&rbuf, 1, MPI_FLOAT, 2, 5, MPI_COMM_WORLD, &status);
			MPI_Recv(&ibuf, 1, MPI_INT, 1, 5, MPI_COMM_WORLD, &status);

			cout << "rank cycle(2)= " << rank << endl;

			cout << "Process 0 recv " << rbuf << " from process 2, " << ibuf << "from process 1\n";
		}
	}

MPI_Finalize();
}