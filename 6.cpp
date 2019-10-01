#include <iostream>
#include "mpi.h"
#define NTIMES 100	//константа, определяющая количество повторений, для получения усредненного результата
using namespace std;
int main(int argc, char **argv)
{
	double time_start, time_finish; //подсчет времени
	int rank, i; 	//ранг процесса, счетчик

	int len; 	//в len возвращается количество символов в имени
			//не превышающее константы MPI_MAX_PROCESSOR_NAME.  

	char *name = new char;

	MPI_Init(&argc, &argv);		//инициализация среды выполнения MPI-программы 
					//(число аргументов,указатель на массив символов)

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	//оперденелие номера процесса(ранга) в коммуникаторе
						///MPI_COMM идентификатор группы
						
	MPI_Get_processor_name(name, &len); ////Возвращает в строке name имя узла, на котором запущен вызвавший процесс

	time_start = MPI_Wtime();	//запуск функции подсчета времени

	for (i = 0; i<NTIMES; i++)
		time_finish = MPI_Wtime();
	cout << "processor " << name << ", process " << rank << "time = " << (time_finish-time_start)/NTIMES << endl;

MPI_Finalize();	//Завершение параллельной части приложения
}